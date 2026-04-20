<?php

class ElvexRunner
{
    private static function decodeUnicode(string $s): string
    {
        if (!function_exists('mb_convert_encoding')) {
            return $s;
        }

        $result = preg_replace_callback(
            '/\\\\u([0-9a-fA-F]{4})/',
            function ($m) {
                return mb_convert_encoding(pack('H*', $m[1]), 'UTF-8', 'UTF-16BE');
            },
            $s
        );

        return $result === null ? $s : $result;
    }

    private static function generateUuidV4(): string
    {
        $data = random_bytes(16);
        $data[6] = chr((ord($data[6]) & 0x0f) | 0x40);
        $data[8] = chr((ord($data[8]) & 0x3f) | 0x80);

        return vsprintf('%s%s-%s-%s-%s-%s%s%s', str_split(bin2hex($data), 4));
    }

    private static function capFirstUtf8(string $s): string
    {
        if ($s === '' || !function_exists('mb_substr')) {
            return $s;
        }

        $first = mb_substr($s, 0, 1, 'UTF-8');
        $rest  = mb_substr($s, 1, null, 'UTF-8');

        return mb_strtoupper($first, 'UTF-8') . $rest;
    }

    private static function buildReplacementFromMatches(string $template, array $matches): string
    {
        $result = $template;
        $indexes = [];

        foreach ($matches as $k => $v) {
            if (is_int($k)) {
                $indexes[] = $k;
            }
        }

        rsort($indexes, SORT_NUMERIC);

        foreach ($indexes as $i) {
            $result = str_replace('\\' . $i, (string)$matches[$i], $result);
        }

        return $result;
    }

    private static function parsePostRules(string $postRules): array
    {
        $rules = [];
        $lines = preg_split('/\R/u', $postRules);
        $pendingPattern = null;

        foreach ($lines as $rawLine) {
            $line = trim($rawLine);

            if ($line === '' || str_starts_with($line, '#') || str_starts_with($line, '//')) {
                continue;
            }

            if (preg_match('/^(.*?)\s*=>\s*(.*)$/u', $line, $m)) {
                $pattern = trim($m[1]);
                $replacement = trim($m[2]);

                if ($pattern !== '') {
                    $rules[] = [
                        'pattern' => $pattern,
                        'replacement' => $replacement,
                    ];
                }

                $pendingPattern = null;
                continue;
            }

            if ($pendingPattern === null) {
                $pendingPattern = $line;
                continue;
            }

            if (preg_match('/^=>\s*(.*)$/u', $line, $m)) {
                $rules[] = [
                    'pattern' => $pendingPattern,
                    'replacement' => trim($m[1]),
                ];
                $pendingPattern = null;
                continue;
            }

            $pendingPattern = $line;
        }

        return $rules;
    }

    private static function applySinglePostRule(string $text, string $pattern, string $replacement): string
    {
        if ($pattern === '') {
            return $text;
        }

        $regex = '~' . str_replace('~', '\\~', $pattern) . '~mu';

        $applyFunction = function (string $func, string $value): string {
            switch ($func) {
                case 'cap':
                    return self::capFirstUtf8($value);
                case 'upper':
                    return function_exists('mb_strtoupper') ? mb_strtoupper($value, 'UTF-8') : strtoupper($value);
                case 'lower':
                    return function_exists('mb_strtolower') ? mb_strtolower($value, 'UTF-8') : strtolower($value);
                default:
                    return $value;
            }
        };

        if (preg_match('/^(cap|upper|lower)\((.*)\)$/u', $replacement, $m)) {
            $func = $m[1];
            $template = $m[2];

            $newText = preg_replace_callback(
                $regex,
                function ($matches) use ($template, $func, $applyFunction) {
                    $rebuilt = self::buildReplacementFromMatches($template, $matches);
                    return $applyFunction($func, $rebuilt);
                },
                $text
            );

            return $newText === null ? $text : $newText;
        }

        $newText = preg_replace($regex, $replacement, $text);
        return $newText === null ? $text : $newText;
    }

    private static function applyPostTransformations(string $text, string $postRules): string
    {
        if (trim($postRules) === '') {
            return $text;
        }

        foreach (self::parsePostRules($postRules) as $rule) {
            $text = self::applySinglePostRule($text, $rule['pattern'], $rule['replacement']);
        }

        return $text;
    }

    private static function sanitizeErrorForUser(string $error, string $dir, string $fileName): string
    {
        $map = [
            $dir . DIRECTORY_SEPARATOR . $fileName . '.rules'   => 'Rules',
            $dir . DIRECTORY_SEPARATOR . $fileName . '.lexicon' => 'Lexicon',
            $dir . DIRECTORY_SEPARATOR . $fileName . '.input'   => 'Input',
            $dir . DIRECTORY_SEPARATOR . $fileName . '.macros'  => 'Macros',
            $dir . DIRECTORY_SEPARATOR . $fileName . '.pattern' => 'Pattern',
            $dir . DIRECTORY_SEPARATOR . $fileName . '.morpho'  => 'Morpho',
        ];

        foreach ($map as $realPath => $label) {
            $quoted = preg_quote($realPath, '~');

            $error = preg_replace(
                '~\bin\s+' . $quoted . '\s*\((\d+)\)~u',
                'in ' . $label . ' ($1)',
                $error
            );

            $error = str_replace($realPath, $label, $error);
        }

        return $error;
    }

    private static function sanitizeCommandForUser(string $cmd): string
    {
        $cmd = preg_replace(
            "~^.*?/elvexlexicon\\b~",
            "elvexlexicon",
            $cmd
        );

        $cmd = preg_replace(
            "~^.*?/elvex\\b~",
            "elvex",
            $cmd
        );

        $cmd = preg_replace(
            "~'[^']*?/[^']*?\\.(rules|lexicon|input|macros|pattern|morpho|output|err|build\\.err|log)'~",
            "'<path>/file.$1'",
            $cmd
        );

        return $cmd ?? 'elvex <commande masquée>';
    }

    private static function stripEmptyAndCommentLines(string $text): string
    {
        $lines = preg_split('/\R/u', $text);
        $kept = [];

        foreach ($lines as $line) {
            $trimmed = trim($line);

            if ($trimmed === '') {
                continue;
            }

            if (str_starts_with($trimmed, '//')) {
                continue;
            }

            $kept[] = $line;
        }

        return implode("\n", $kept);
    }

    private static function deleteDirectory(string $dir): void
    {
        if (!is_dir($dir)) {
            return;
        }

        $items = scandir($dir);
        if ($items === false) {
            return;
        }

        foreach ($items as $item) {
            if ($item === '.' || $item === '..') {
                continue;
            }

            $path = $dir . DIRECTORY_SEPARATOR . $item;

            if (is_dir($path)) {
                self::deleteDirectory($path);
                @rmdir($path);
            } elseif (is_file($path) || is_link($path)) {
                @unlink($path);
            }
        }
    }

    private static function cleanCurrentSessionDirectory(string $dir, int $maxAgeSeconds): void
    {
        if (!is_dir($dir)) {
            return;
        }

        $now = time();

        $items = scandir($dir);
        if ($items === false) {
            return;
        }

        foreach ($items as $item) {
            if ($item === '.' || $item === '..') {
                continue;
            }

            $path = $dir . DIRECTORY_SEPARATOR . $item;

            // On récupère la date de modification
            $mtime = @filemtime($path);
            if ($mtime === false) {
                continue;
            }

            // Si trop récent → on garde
            if (($now - $mtime) < $maxAgeSeconds) {
                continue;
            }

            // Sinon on supprime
            if (is_dir($path)) {
                self::deleteDirectory($path);
                @rmdir($path);
            } elseif (is_file($path) || is_link($path)) {
                @unlink($path);
            }
        }
    }

    public static function run(array $payload): array
    {
        $config = config();
        $runner = $config['elvex'] ?? [];

        $macros  = self::decodeUnicode((string)($payload['macros'] ?? ''));
        $rules   = self::decodeUnicode((string)($payload['rules'] ?? ''));
        $lexicon = self::decodeUnicode((string)($payload['lexicon'] ?? ''));
        $pattern = self::decodeUnicode((string)($payload['pattern'] ?? ''));
        $morpho  = self::decodeUnicode((string)($payload['morpho'] ?? ''));
        $input   = self::decodeUnicode((string)($payload['input'] ?? ''));
        $post    = self::decodeUnicode((string)($payload['post'] ?? ''));

        $baseTmp = $runner['tmp_dir'] ?? '/var/www/elvex/tmp';

        if (!is_dir($baseTmp) && !mkdir($baseTmp, 0770, true)) {
            throw new RuntimeException('Impossible de créer le répertoire temporaire de base : ' . $baseTmp);
        }

        $sessionId = session_id();
        if ($sessionId === '') {
            throw new RuntimeException('Session PHP introuvable.');
        }

        $safeSessionId = preg_replace('/[^A-Za-z0-9_-]/', '_', $sessionId);
        $dir = $baseTmp . DIRECTORY_SEPARATOR . $safeSessionId;

        if (!is_dir($dir) && !mkdir($dir, 0770, true)) {
            throw new RuntimeException('Impossible de créer le répertoire temporaire de session : ' . $dir);
        }

        // Nettoie les anciens fichiers de la session courante avant une nouvelle exécution
        self::cleanCurrentSessionDirectory($dir, 4 * 60);

        $fileName = self::generateUuidV4();

        $patternForBuild = self::stripEmptyAndCommentLines($pattern);
        $morphoForBuild  = self::stripEmptyAndCommentLines($morpho);

        if ($patternForBuild !== '') {
            $whichLexicon = trim((string)shell_exec('command -v elvexlexicon 2>/dev/null'));
            if ($whichLexicon === '') {
                throw new RuntimeException('La commande elvexlexicon est introuvable sur le serveur.');
            }

            $lexiconCmdParts = [escapeshellcmd($whichLexicon)];

            if ($macros !== '') {
                $macrosFile = $dir . DIRECTORY_SEPARATOR . $fileName . '.macros';
                file_put_contents($macrosFile, $macros);
                $lexiconCmdParts[] = '-macrosFile ' . escapeshellarg($macrosFile);
            }

            $patternFile = $dir . DIRECTORY_SEPARATOR . $fileName . '.pattern';
            file_put_contents($patternFile, $patternForBuild);
            $lexiconCmdParts[] = '-patternFile ' . escapeshellarg($patternFile);

            if ($morphoForBuild !== '') {
                $morphoFile = $dir . DIRECTORY_SEPARATOR . $fileName . '.morpho';
                file_put_contents($morphoFile, $morphoForBuild);
                $lexiconCmdParts[] = '-morphoFile ' . escapeshellarg($morphoFile);
            }

            $lexiconCmdParts[] = '-compactedLexiconDirectory ' . escapeshellarg($dir);
            $lexiconCmdParts[] = '-compactedLexiconFile ' . escapeshellarg($fileName);

            $errorFileBuild = $dir . DIRECTORY_SEPARATOR . $fileName . '.build.err';
            $buildCmd = implode(' ', $lexiconCmdParts) . ' build 2> ' . escapeshellarg($errorFileBuild);

            $buildExitCode = 0;
            exec($buildCmd, $unusedBuildOutput, $buildExitCode);

            $buildError = file_exists($errorFileBuild) ? (file_get_contents($errorFileBuild) ?: '') : '';

            if ($buildExitCode !== 0) {
                $buildError = self::sanitizeErrorForUser($buildError, $dir, $fileName);
                $buildError .= "\n\n--- Commande exécutée ---\n" . self::sanitizeCommandForUser($buildCmd) . "\n";

                return [
                    'message' => 'Exécution terminée avec erreur.',
                    'exitCode' => $buildExitCode,
                    'output' => '',
                    'error' => $buildError,
                    'logUrl' => '',
                ];
            }
        }

        $whichElvex = trim((string)shell_exec('command -v elvex 2>/dev/null'));
        if ($whichElvex === '') {
            throw new RuntimeException('La commande elvex est introuvable sur le serveur.');
        }

        $cmdParts = [escapeshellcmd($whichElvex)];

        if ($macros !== '') {
            $macrosFile = $dir . DIRECTORY_SEPARATOR . $fileName . '.macros';
            if (!file_exists($macrosFile)) {
                file_put_contents($macrosFile, $macros);
            }
            $cmdParts[] = '-macrosFile ' . escapeshellarg($macrosFile);
        }

        if ($rules !== '') {
            $rulesFile = $dir . DIRECTORY_SEPARATOR . $fileName . '.rules';
            file_put_contents($rulesFile, $rules);
            $cmdParts[] = '-rulesFile ' . escapeshellarg($rulesFile);
        }

        if ($lexicon !== '') {
            $lexiconFile = $dir . DIRECTORY_SEPARATOR . $fileName . '.lexicon';
            file_put_contents($lexiconFile, $lexicon);
            $cmdParts[] = '-lexiconFile ' . escapeshellarg($lexiconFile);
        }

        if ($input !== '') {
            $inputFile = $dir . DIRECTORY_SEPARATOR . $fileName . '.input';
            file_put_contents($inputFile, $input);
            $cmdParts[] = '-inputFile ' . escapeshellarg($inputFile);
        }

        if ($pattern !== '') {
            $cmdParts[] = '-compactedLexiconDirectory ' . escapeshellarg($dir);
            $cmdParts[] = '-compactedLexiconFile ' . escapeshellarg($fileName);
        }

        $outputFile = $dir . DIRECTORY_SEPARATOR . $fileName . '.output';
        $errorFile  = $dir . DIRECTORY_SEPARATOR . $fileName . '.err';
        $traceFile  = $dir . DIRECTORY_SEPARATOR . $fileName . '.log';

        $cmd = implode(' ', $cmdParts)
             . ' > ' . escapeshellarg($outputFile)
             . ' 2> ' . escapeshellarg($errorFile);

        $exitCode = 0;
        exec($cmd, $unusedOutput, $exitCode);

        $output = file_exists($outputFile) ? (file_get_contents($outputFile) ?: '') : '';
        $error  = file_exists($errorFile) ? (file_get_contents($errorFile) ?: '') : '';
        $logUrl = '';

        if ($exitCode === 0) {
            if (trim($output) !== '') {
                $output = self::applyPostTransformations($output, $post);
            } else {
                $traceCmd = implode(' ', $cmdParts)
                    . ' --trace'
                    . ' > ' . escapeshellarg($traceFile)
                    . ' 2> /dev/null';

                $traceExitCode = 0;
                exec($traceCmd, $unusedTraceOutput, $traceExitCode);

                if (file_exists($traceFile)) {
                    $logUrl = 'view_log.php?uuid=' . urlencode($fileName);
                }

                $error .= "\n\nAucune sortie n'a été produite malgré une exécution sans erreur.";
            }
        } else {
            $error = self::sanitizeErrorForUser($error, $dir, $fileName);
            $error .= "\n\n--- Commande exécutée ---\n" . self::sanitizeCommandForUser($cmd) . "\n";
        }

        return [
            'message' => $exitCode === 0 ? 'Exécution terminée.' : 'Exécution terminée avec erreur.',
            'exitCode' => $exitCode,
            'output' => $output,
            'error' => $error,
            'logUrl' => $logUrl,
        ];
    }
}