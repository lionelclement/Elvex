<?php
function config(): array
{
    static $config = null;
    if ($config === null) {
        $config = require __DIR__ . '/../../config/config.php';
    }
    return $config;
}

function app_base_url(): string
{
    return rtrim(config()['app']['base_url'] ?? '', '/');
}

function url_path(string $path = ''): string
{
    $base = app_base_url();

    if ($path === '') {
        return ($base === '' ? '' : $base) . '/index.php';
    }

    if (str_contains($path, '?')) {
        [$route, $query] = explode('?', $path, 2);
        return ($base === '' ? '' : $base) . '/index.php?route=' . ltrim($route, '/') . '&' . $query;
    }

    return ($base === '' ? '' : $base) . '/index.php?route=' . ltrim($path, '/');
}

function redirect(string $path): void
{
    header('Location: ' . url_path($path));
    exit;
}

function e(?string $value): string
{
    return htmlspecialchars((string)$value, ENT_QUOTES, 'UTF-8');
}

function csrf_token(): string
{
    if (empty($_SESSION['_csrf'])) {
        $_SESSION['_csrf'] = bin2hex(random_bytes(16));
    }
    return $_SESSION['_csrf'];
}

function require_csrf(): void
{
    $token = $_POST['_csrf'] ?? '';
    if (!hash_equals($_SESSION['_csrf'] ?? '', $token)) {
        http_response_code(403);
        exit('CSRF invalide');
    }
}

function flash(string $key, ?string $value = null)
{
    if ($value !== null) {
        $_SESSION['_flash'][$key] = $value;
        return null;
    }
    $msg = $_SESSION['_flash'][$key] ?? null;
    unset($_SESSION['_flash'][$key]);
    return $msg;
}

function current_user(): ?array
{
    return $_SESSION['user'] ?? null;
}

function is_logged_in(): bool
{
    return current_user() !== null;
}

function password_is_strong(string $password): bool
{
    if (strlen($password) < 12) return false;
    if (!preg_match('/[A-Z]/', $password)) return false;
    if (!preg_match('/[a-z]/', $password)) return false;
    if (!preg_match('/[0-9]/', $password)) return false;
    if (!preg_match('/[^a-zA-Z0-9]/', $password)) return false;
    return true;
}
