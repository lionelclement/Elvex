<?php
class Mailer
{
    public static function sendSignupCode(string $email, string $displayName, string $code): bool
    {
        $app = config()['app'];
        $subject = '[' . ($app['app_name'] ?? 'ELVEX') . '] Code de création de compte';
        $message = "Bonjour " . $displayName . ",\n\n"
            . "Voici votre code de création de compte : " . $code . "\n\n"
            . "Ce code expire dans 15 minutes.\n";
        $headers = [
            'From: ' . ($app['mail_from'] ?? 'no-reply@example.com'),
            'Content-Type: text/plain; charset=UTF-8'
        ];

        return mail($email, $subject, $message, implode("\r\n", $headers));
    }

    public static function sendPasswordResetCode(string $email, string $displayName, string $code): bool
    {
        $app = config()['app'];
        $subject = '[' . ($app['app_name'] ?? 'ELVEX') . '] Réinitialisation du mot de passe';
        $message = "Bonjour " . $displayName . ",\n\n"
            . "Voici votre code de réinitialisation : " . $code . "\n\n"
            . "Ce code expire dans 30 minutes.\n";
        $headers = [
            'From: ' . ($app['mail_from'] ?? 'no-reply@example.com'),
            'Content-Type: text/plain; charset=UTF-8'
        ];

        return mail($email, $subject, $message, implode("\r\n", $headers));
    }
}
