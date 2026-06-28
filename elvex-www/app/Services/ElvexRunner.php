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



    private static function sessionDirectory(): string
    {
        $config = config();
        $runner = $config['elvex'] ?? [];
        $baseTmp = $runner['tmp_dir'] ?? (__DIR__ . '/../../tmp');

        if (!is_dir($baseTmp) && !mkdir($baseTmp, 0770, true)) {
            throw new RuntimeException('Impossible de créer le répertoire temporaire de base : ' . $baseTmp);
        }

        $sessionId = session_id();
        if ($sessionId === '') {
            throw new RuntimeException('Session PHP introuvable.');
        }

        $safeSessionId = preg_replace('/[^A-Za-z0-9_-]/', '_', $sessionId);
        $dir = rtrim($baseTmp, DIRECTORY_SEPARATOR) . DIRECTORY_SEPARATOR . $safeSessionId;

        if (!is_dir($dir) && !mkdir($dir, 0770, true)) {
            throw new RuntimeException('Impossible de créer le répertoire temporaire de session : ' . $dir);
        }

        return $dir;
    }

    private static function serverDirectory(): string
    {
        $dir = self::sessionDirectory() . DIRECTORY_SEPARATOR . 'server';
        if (!is_dir($dir) && !mkdir($dir, 0770, true)) {
            throw new RuntimeException('Impossible de créer le répertoire serveur : ' . $dir);
        }
        return $dir;
    }

    private static function serverStateFile(): string
    {
        return self::serverDirectory() . DIRECTORY_SEPARATOR . 'server.json';
    }

    private static function readServerState(): array
    {
        $file = self::serverStateFile();
        if (!is_file($file)) {
            return [];
        }

        $json = file_get_contents($file);
        $state = json_decode($json ?: '', true);
        return is_array($state) ? $state : [];
    }

    private static function writeServerState(array $state): void
    {
        file_put_contents(self::serverStateFile(), json_encode($state, JSON_PRETTY_PRINT | JSON_UNESCAPED_UNICODE));
    }

    private static function processIsRunning(int $pid): bool
    {
        if ($pid <= 0) {
            return false;
        }

        exec('kill -0 ' . (int)$pid . ' 2>/dev/null', $unused, $exitCode);
        return $exitCode === 0;
    }

    private static function killProcess(int $pid): void
    {
        if ($pid <= 0) {
            return;
        }

        exec('kill -TERM ' . (int)$pid . ' 2>/dev/null');
        usleep(150000);

        if (self::processIsRunning($pid)) {
            exec('kill -KILL ' . (int)$pid . ' 2>/dev/null');
        }
    }

    private static function ensureFifo(string $path): void
    {
        if (file_exists($path)) {
            if (!is_link($path) && filetype($path) === 'fifo') {
                return;
            }
            @unlink($path);
        }

        if (function_exists('posix_mkfifo')) {
            if (!posix_mkfifo($path, 0660)) {
                throw new RuntimeException('Impossible de créer le pipe serveur : ' . $path);
            }
            return;
        }

        exec('mkfifo ' . escapeshellarg($path) . ' 2>/dev/null', $unused, $exitCode);
        if ($exitCode !== 0 || !file_exists($path)) {
            throw new RuntimeException('Impossible de créer le pipe serveur : ' . $path);
        }
        @chmod($path, 0660);
    }

    private static function prepareCommandParts(array $payload, string $dir, string $fileName, bool $includeInputFile): array
    {
        $macros  = self::decodeUnicode((string)($payload['macros'] ?? ''));
        $rules   = self::decodeUnicode((string)($payload['rules'] ?? ''));
        $lexicon = self::decodeUnicode((string)($payload['lexicon'] ?? ''));
        $pattern = self::decodeUnicode((string)($payload['pattern'] ?? ''));
        $morpho  = self::decodeUnicode((string)($payload['morpho'] ?? ''));
        $input   = self::decodeUnicode((string)($payload['input'] ?? ''));

        $patternForBuild = self::stripEmptyAndCommentLines($pattern);
        $morphoForBuild  = self::stripEmptyAndCommentLines($morpho);

        if ($patternForBuild !== '') {
            $whichLexicon = trim((string)shell_exec('command -v elvexlexicon 2>/dev/null'));
            if ($whichLexicon === '') {
                throw new RuntimeException('The elvexlexicon command was not found on the server.');
            }

            $lexiconCmdParts = [escapeshellcmd($whichLexicon)];

            if ($macros !== '') {
                $macrosFile = $dir . DIRECTORY_SEPARATOR . $fileName . '.macros';
                file_put_contents($macrosFile, $macros);
                $lexiconCmdParts[] = '--macros-file ' . escapeshellarg($macrosFile);
            }

            $patternFile = $dir . DIRECTORY_SEPARATOR . $fileName . '.pattern';
            file_put_contents($patternFile, $patternForBuild);
            $lexiconCmdParts[] = '--pattern-file ' . escapeshellarg($patternFile);

            if ($morphoForBuild !== '') {
                $morphoFile = $dir . DIRECTORY_SEPARATOR . $fileName . '.morpho';
                file_put_contents($morphoFile, $morphoForBuild);
                $lexiconCmdParts[] = '--morpho-file ' . escapeshellarg($morphoFile);
            }

            $lexiconCmdParts[] = '--compacted-lexicon-file ' . escapeshellarg($dir . DIRECTORY_SEPARATOR . $fileName);

            $errorFileBuild = $dir . DIRECTORY_SEPARATOR . $fileName . '.build.err';
            $buildCmd = implode(' ', $lexiconCmdParts) . ' build 2> ' . escapeshellarg($errorFileBuild);

            $buildExitCode = 0;
            exec($buildCmd, $unusedBuildOutput, $buildExitCode);

            if ($buildExitCode !== 0) {
                $buildError = file_exists($errorFileBuild) ? (file_get_contents($errorFileBuild) ?: '') : '';
                $buildError = self::sanitizeErrorForUser($buildError, $dir, $fileName);
                $buildError .= "\n\n--- Executed command ---\n" . self::sanitizeCommandForUser($buildCmd) . "\n";
                throw new RuntimeException($buildError);
            }
        }

        $whichElvex = trim((string)shell_exec('command -v elvex 2>/dev/null'));
        if ($whichElvex === '') {
            throw new RuntimeException('The elvex command was not found on the server.');
        }

        $cmdParts = [escapeshellcmd($whichElvex)];

        if ($macros !== '') {
            $macrosFile = $dir . DIRECTORY_SEPARATOR . $fileName . '.macros';
            if (!file_exists($macrosFile)) {
                file_put_contents($macrosFile, $macros);
            }
            $cmdParts[] = '--macros-file ' . escapeshellarg($macrosFile);
        }

        if ($rules !== '') {
            $rulesFile = $dir . DIRECTORY_SEPARATOR . $fileName . '.rules';
            file_put_contents($rulesFile, $rules);
            $cmdParts[] = '--rules-file ' . escapeshellarg($rulesFile);
        }

        if ($lexicon !== '') {
            $lexiconFile = $dir . DIRECTORY_SEPARATOR . $fileName . '.lexicon';
            file_put_contents($lexiconFile, $lexicon);
            $cmdParts[] = '--lexicon-file ' . escapeshellarg($lexiconFile);
        }

        if ($includeInputFile && $input !== '') {
            $inputFile = $dir . DIRECTORY_SEPARATOR . $fileName . '.input';
            file_put_contents($inputFile, $input);
            $cmdParts[] = '--input-file ' . escapeshellarg($inputFile);
        }

        if ($pattern !== '') {
            $cmdParts[] = '--compacted-lexicon-file ' . escapeshellarg($dir . DIRECTORY_SEPARATOR . $fileName);
        }

        return $cmdParts;
    }

    public static function serverStatus(): array
    {
        $state = self::readServerState();
        $running = self::processIsRunning((int)($state['pid'] ?? 0));

        if (!$running && !empty($state)) {
            $state['running'] = false;
            self::writeServerState($state);
        }

        return [
            'running' => $running,
            'pid' => (int)($state['pid'] ?? 0),
            'startedAt' => $state['startedAt'] ?? null,
            'command' => isset($state['command']) ? self::sanitizeCommandForUser((string)$state['command']) : '',
        ];
    }

    public static function startServer(array $payload): array
    {
        self::stopServer();

        $serverDir = self::serverDirectory();
        self::deleteDirectory($serverDir);
        if (!is_dir($serverDir) && !mkdir($serverDir, 0770, true)) {
            throw new RuntimeException('Impossible de créer le répertoire serveur : ' . $serverDir);
        }

        $fileName = 'server';
        $cmdParts = self::prepareCommandParts($payload, $serverDir, $fileName, false);
        $cmdParts[] = '--server-stdio';

        $stdinFifo = $serverDir . DIRECTORY_SEPARATOR . 'stdin.fifo';
        $stdoutFile = $serverDir . DIRECTORY_SEPARATOR . 'stdout.log';
        $stderrFile = $serverDir . DIRECTORY_SEPARATOR . 'stderr.log';

        self::ensureFifo($stdinFifo);
        file_put_contents($stdoutFile, '');
        file_put_contents($stderrFile, '');

        $cmd = implode(' ', $cmdParts);
        $startCmd = 'nohup sh -c ' . escapeshellarg('exec ' . $cmd . ' < ' . escapeshellarg($stdinFifo) . ' >> ' . escapeshellarg($stdoutFile) . ' 2>> ' . escapeshellarg($stderrFile)) . ' >/dev/null 2>&1 & echo $!';
        $pid = (int)trim((string)shell_exec($startCmd));

        if ($pid <= 0) {
            throw new RuntimeException('Unable to start the Elvex server.');
        }

        $keeperCmd = 'nohup tail -f /dev/null > ' . escapeshellarg($stdinFifo) . ' 2>/dev/null & echo $!';
        $keeperPid = (int)trim((string)shell_exec($keeperCmd));

        usleep(200000);

        $state = [
            'pid' => $pid,
            'keeperPid' => $keeperPid,
            'startedAt' => date('c'),
            'command' => $cmd,
            'stdin' => $stdinFifo,
            'stdout' => $stdoutFile,
            'stderr' => $stderrFile,
            'post' => self::decodeUnicode((string)($payload['post'] ?? '')),
        ];
        self::writeServerState($state);

        if (!self::processIsRunning($pid)) {
            $error = file_exists($stderrFile) ? (file_get_contents($stderrFile) ?: '') : '';
            throw new RuntimeException($error !== '' ? $error : 'The Elvex server stopped immediately.');
        }

        return [
            'message' => 'Elvex server started.',
            'running' => true,
            'pid' => $pid,
            'command' => self::sanitizeCommandForUser($cmd),
        ];
    }

    public static function stopServer(): array
    {
        $state = self::readServerState();

        self::killProcess((int)($state['keeperPid'] ?? 0));
        self::killProcess((int)($state['pid'] ?? 0));

        if (!empty($state)) {
            $state['running'] = false;
            $state['stoppedAt'] = date('c');
            self::writeServerState($state);
        }

        return [
            'message' => 'Elvex server stopped.',
            'running' => false,
        ];
    }

    public static function sendToServer(string $input): array
    {
        $input = self::decodeUnicode($input);
        $input = trim($input);

        if ($input === '') {
            throw new RuntimeException('Empty input.');
        }

        if (str_contains($input, "\n") || str_contains($input, "\r")) {
            throw new RuntimeException('Le mode serveur attend un seul input par envoi. Envoie une seule ligne à la fois.');
        }

        $state = self::readServerState();
        $pid = (int)($state['pid'] ?? 0);

        if (!self::processIsRunning($pid)) {
            throw new RuntimeException('The Elvex server is not running.');
        }

        $stdinFifo = (string)($state['stdin'] ?? '');
        $stdoutFile = (string)($state['stdout'] ?? '');
        $stderrFile = (string)($state['stderr'] ?? '');

        if ($stdinFifo === '' || $stdoutFile === '' || !file_exists($stdinFifo)) {
            throw new RuntimeException('Invalid server state. Restart the Elvex server.');
        }

        $lockFile = self::serverDirectory() . DIRECTORY_SEPARATOR . 'server.lock';
        $lock = fopen($lockFile, 'c');
        if (!$lock) {
            throw new RuntimeException('Impossible de verrouiller le serveur Elvex.');
        }

        try {
            if (!flock($lock, LOCK_EX)) {
                throw new RuntimeException('Impossible de verrouiller le serveur Elvex.');
            }

            clearstatcache(true, $stdoutFile);
            $offset = is_file($stdoutFile) ? (int)filesize($stdoutFile) : 0;

            $fh = fopen($stdinFifo, 'w');
            if (!$fh) {
                throw new RuntimeException('Impossible d’écrire dans le serveur Elvex.');
            }
            fwrite($fh, $input . "\n");
            fclose($fh);

            $timeout = (int)((config()['elvex']['server_timeout_seconds'] ?? 30));
            $deadline = microtime(true) + max(1, $timeout);
            $chunk = '';
            $separator = "\x1e";

            while (microtime(true) < $deadline) {
                clearstatcache(true, $stdoutFile);
                if (is_file($stdoutFile) && filesize($stdoutFile) > $offset) {
                    $data = file_get_contents($stdoutFile, false, null, $offset);
                    $chunk = $data === false ? '' : $data;

                    $pos = strpos($chunk, $separator);
                    if ($pos !== false) {
                        $rawOutput = substr($chunk, 0, $pos);
                        $output = rtrim($rawOutput, "\r\n");
                        $output = self::applyPostTransformations($output, (string)($state['post'] ?? ''));

                        flock($lock, LOCK_UN);
                        fclose($lock);

                        return [
                            'message' => 'Input traité.',
                            'running' => self::processIsRunning($pid),
                            'input' => $input,
                            'output' => $output,
                            'error' => '',
                        ];
                    }
                }

                if (!self::processIsRunning($pid)) {
                    $error = is_file($stderrFile) ? (file_get_contents($stderrFile) ?: '') : '';
                    throw new RuntimeException($error !== '' ? $error : 'The Elvex server stopped while processing.');
                }

                usleep(100000);
            }

            throw new RuntimeException('Timeout : aucune réponse complète reçue du serveur Elvex.');
        } finally {
            if (is_resource($lock)) {
                @flock($lock, LOCK_UN);
                @fclose($lock);
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

        $baseTmp = $runner['tmp_dir'] ?? 'tmp';

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
                throw new RuntimeException('The elvexlexicon command was not found on the server.');
            }

            $lexiconCmdParts = [escapeshellcmd($whichLexicon)];

            if ($macros !== '') {
                $macrosFile = $dir . DIRECTORY_SEPARATOR . $fileName . '.macros';
                file_put_contents($macrosFile, $macros);
                $lexiconCmdParts[] = '--macros-file ' . escapeshellarg($macrosFile);
            }

            $patternFile = $dir . DIRECTORY_SEPARATOR . $fileName . '.pattern';
            file_put_contents($patternFile, $patternForBuild);
            $lexiconCmdParts[] = '--pattern-file ' . escapeshellarg($patternFile);

            if ($morphoForBuild !== '') {
                $morphoFile = $dir . DIRECTORY_SEPARATOR . $fileName . '.morpho';
                file_put_contents($morphoFile, $morphoForBuild);
                $lexiconCmdParts[] = '--morpho-file ' . escapeshellarg($morphoFile);
            }

            $lexiconCmdParts[] = '--compacted-lexicon-file ' . escapeshellarg($dir) . '/'. escapeshellarg($fileName);

            $errorFileBuild = $dir . DIRECTORY_SEPARATOR . $fileName . '.build.err';
            $buildCmd = implode(' ', $lexiconCmdParts) . ' build 2> ' . escapeshellarg($errorFileBuild);

            $buildExitCode = 0;
            exec($buildCmd, $unusedBuildOutput, $buildExitCode);

            $buildError = file_exists($errorFileBuild) ? (file_get_contents($errorFileBuild) ?: '') : '';

            if ($buildExitCode !== 0) {
                $buildError = self::sanitizeErrorForUser($buildError, $dir, $fileName);
                $buildError .= "\n\n--- Executed command ---\n" . self::sanitizeCommandForUser($buildCmd) . "\n";

                return [
                    'message' => 'Execution finished with an error.',
                    'exitCode' => $buildExitCode,
                    'output' => '',
                    'error' => $buildError,
                    'logUrl' => '',
                ];
            }
        }

        $whichElvex = trim((string)shell_exec('command -v elvex 2>/dev/null'));
        if ($whichElvex === '') {
            throw new RuntimeException('The elvex command was not found on the server.');
        }

        $cmdParts = [escapeshellcmd($whichElvex)];

        if ($macros !== '') {
            $macrosFile = $dir . DIRECTORY_SEPARATOR . $fileName . '.macros';
            if (!file_exists($macrosFile)) {
                file_put_contents($macrosFile, $macros);
            }
            $cmdParts[] = '--macros-file ' . escapeshellarg($macrosFile);
        }

        if ($rules !== '') {
            $rulesFile = $dir . DIRECTORY_SEPARATOR . $fileName . '.rules';
            file_put_contents($rulesFile, $rules);
            $cmdParts[] = '--rules-file ' . escapeshellarg($rulesFile);
        }

        if ($lexicon !== '') {
            $lexiconFile = $dir . DIRECTORY_SEPARATOR . $fileName . '.lexicon';
            file_put_contents($lexiconFile, $lexicon);
            $cmdParts[] = '--lexicon-file ' . escapeshellarg($lexiconFile);
        }

        if ($input !== '') {
            $inputFile = $dir . DIRECTORY_SEPARATOR . $fileName . '.input';
            file_put_contents($inputFile, $input);
            $cmdParts[] = '--input-file ' . escapeshellarg($inputFile);
        }

        if ($pattern !== '') {
            $cmdParts[] = '--compacted-lexicon-file ' . escapeshellarg($dir). '/' . escapeshellarg($fileName);
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

                $error .= "\n\nNo output was produced, even though execution completed without an error.";
            }
        } else {
            $error = self::sanitizeErrorForUser($error, $dir, $fileName);
            $error .= "\n\n--- Executed command ---\n" . self::sanitizeCommandForUser($cmd) . "\n";
        }

        return [
            'message' => $exitCode === 0 ? 'Execution finished.' : 'Execution finished with an error.',
            'exitCode' => $exitCode,
            'output' => $output,
            'error' => $error,
            'logUrl' => $logUrl,
        ];
    }
}