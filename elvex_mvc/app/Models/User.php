<?php
require_once __DIR__ . '/../Core/Database.php';

class User
{
    public static function findByEmail(string $email): ?array
    {
        $pdo = Database::getConnection();
        $stmt = $pdo->prepare('SELECT * FROM users WHERE email = ? LIMIT 1');
        $stmt->execute([$email]);
        $row = $stmt->fetch();
        return $row ?: null;
    }

    public static function findById(int $id): ?array
    {
        $pdo = Database::getConnection();
        $stmt = $pdo->prepare('SELECT * FROM users WHERE id = ? LIMIT 1');
        $stmt->execute([$id]);
        $row = $stmt->fetch();
        return $row ?: null;
    }

    public static function createPending(string $email, string $displayName, string $password, string $code): int
    {
        $pdo = Database::getConnection();
        $existing = self::findByEmail($email);

        $passwordHash = password_hash($password, PASSWORD_DEFAULT);
        $signupCodeHash = password_hash($code, PASSWORD_DEFAULT);

        if ($existing) {
            $stmt = $pdo->prepare('
                UPDATE users
                SET display_name = ?,
                    password_hash = ?,
                    signup_code = ?,
                    signup_code_expires_at = DATE_ADD(NOW(), INTERVAL 15 MINUTE),
                    is_verified = 0,
                    updated_at = NOW()
                WHERE email = ?
            ');
            $stmt->execute([$displayName, $passwordHash, $signupCodeHash, $email]);
            return (int)$existing['id'];
        }

        $stmt = $pdo->prepare('
            INSERT INTO users (
                email, display_name, password_hash, signup_code, signup_code_expires_at, is_verified, created_at, updated_at
            ) VALUES (
                ?, ?, ?, ?, DATE_ADD(NOW(), INTERVAL 15 MINUTE), 0, NOW(), NOW()
            )
        ');
        $stmt->execute([$email, $displayName, $passwordHash, $signupCodeHash]);
        return (int)$pdo->lastInsertId();
    }

    public static function verifySignupCode(string $email, string $code): ?array
    {
        $user = self::findByEmail($email);
        if (!$user) return null;
        if (empty($user['signup_code']) || empty($user['signup_code_expires_at'])) return null;
        if (strtotime($user['signup_code_expires_at']) < time()) return null;
        if (!password_verify($code, $user['signup_code'])) return null;

        $pdo = Database::getConnection();
        $stmt = $pdo->prepare('
            UPDATE users
            SET is_verified = 1, signup_code = NULL, signup_code_expires_at = NULL, updated_at = NOW()
            WHERE id = ?
        ');
        $stmt->execute([$user['id']]);

        return self::findById((int)$user['id']);
    }

    public static function verifyPassword(string $email, string $password): ?array
    {
        $user = self::findByEmail($email);
        if (!$user) return null;
        if ((int)$user['is_verified'] !== 1) return null;
        if (empty($user['password_hash'])) return null;
        if (!password_verify($password, $user['password_hash'])) return null;
        return $user;
    }

    public static function setPasswordResetToken(string $email, string $token): bool
    {
        $user = self::findByEmail($email);
        if (!$user || (int)$user['is_verified'] !== 1) return false;

        $pdo = Database::getConnection();
        $stmt = $pdo->prepare('
            UPDATE users
            SET password_reset_token = ?,
                password_reset_expires_at = DATE_ADD(NOW(), INTERVAL 30 MINUTE),
                updated_at = NOW()
            WHERE id = ?
        ');
        return $stmt->execute([password_hash($token, PASSWORD_DEFAULT), $user['id']]);
    }

    public static function resetPasswordWithToken(string $email, string $token, string $newPassword): bool
    {
        $user = self::findByEmail($email);
        if (!$user) return false;
        if (empty($user['password_reset_token']) || empty($user['password_reset_expires_at'])) return false;
        if (strtotime($user['password_reset_expires_at']) < time()) return false;
        if (!password_verify($token, $user['password_reset_token'])) return false;

        $pdo = Database::getConnection();
        $stmt = $pdo->prepare('
            UPDATE users
            SET password_hash = ?,
                password_reset_token = NULL,
                password_reset_expires_at = NULL,
                updated_at = NOW()
            WHERE id = ?
        ');
        return $stmt->execute([password_hash($newPassword, PASSWORD_DEFAULT), $user['id']]);
    }
}
