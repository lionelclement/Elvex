<?php
session_start();

$uuid = $_GET['uuid'] ?? '';
if ($uuid === '') {
    http_response_code(400);
    exit('UUID manquant');
}

$sessionId = session_id();
if ($sessionId === '') {
    http_response_code(500);
    exit('Session introuvable');
}

$safeSessionId = preg_replace('/[^A-Za-z0-9_-]/', '_', $sessionId);

$configFile = __DIR__ . '/config/config.php';
$config = is_file($configFile) ? require $configFile : [];
$baseTmp = $config['elvex']['tmp_dir'] ?? (__DIR__ . '/tmp');
$logFile = $baseTmp . DIRECTORY_SEPARATOR . $safeSessionId . DIRECTORY_SEPARATOR . $uuid . '.log';

if (!is_file($logFile)) {
    http_response_code(404);
    exit('Log introuvable');
}

header('Content-Type: text/html; charset=UTF-8');
readfile($logFile);