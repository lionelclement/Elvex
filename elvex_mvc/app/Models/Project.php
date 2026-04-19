<?php
require_once __DIR__ . '/../Core/Database.php';

class Project
{
    public static function allByUser(int $userId): array
    {
        $pdo = Database::getConnection();
        $stmt = $pdo->prepare('SELECT * FROM projects WHERE user_id = ? ORDER BY updated_at DESC, id DESC');
        $stmt->execute([$userId]);
        return $stmt->fetchAll();
    }

    public static function findByIdForUser(int $id, int $userId): ?array
    {
        $pdo = Database::getConnection();
        $stmt = $pdo->prepare('SELECT * FROM projects WHERE id = ? AND user_id = ? LIMIT 1');
        $stmt->execute([$id, $userId]);
        $row = $stmt->fetch();
        return $row ?: null;
    }

    public static function create(int $userId, array $payload): int
    {
        $pdo = Database::getConnection();
        $stmt = $pdo->prepare('
            INSERT INTO projects (
                user_id, name, macros, rules, lexicon, pattern, morpho, post_morpho, input_text, data_json, created_at, updated_at
            ) VALUES (
                :user_id, :name, :macros, :rules, :lexicon, :pattern, :morpho, :post_morpho, :input_text, :data_json, NOW(), NOW()
            )
        ');

        $stmt->execute([
            ':user_id' => $userId,
            ':name' => $payload['name'],
            ':macros' => $payload['macros'],
            ':rules' => $payload['rules'],
            ':lexicon' => $payload['lexicon'],
            ':pattern' => $payload['pattern'],
            ':morpho' => $payload['morpho'],
            ':post_morpho' => $payload['post'],
            ':input_text' => $payload['input'],
            ':data_json' => json_encode($payload, JSON_UNESCAPED_UNICODE | JSON_UNESCAPED_SLASHES),
        ]);

        return (int)$pdo->lastInsertId();
    }

    public static function update(int $id, int $userId, array $payload): void
    {
        $pdo = Database::getConnection();
        $stmt = $pdo->prepare('
            UPDATE projects
            SET name = :name,
                macros = :macros,
                rules = :rules,
                lexicon = :lexicon,
                pattern = :pattern,
                morpho = :morpho,
                post_morpho = :post_morpho,
                input_text = :input_text,
                data_json = :data_json,
                updated_at = NOW()
            WHERE id = :id AND user_id = :user_id
        ');

        $stmt->execute([
            ':id' => $id,
            ':user_id' => $userId,
            ':name' => $payload['name'],
            ':macros' => $payload['macros'],
            ':rules' => $payload['rules'],
            ':lexicon' => $payload['lexicon'],
            ':pattern' => $payload['pattern'],
            ':morpho' => $payload['morpho'],
            ':post_morpho' => $payload['post'],
            ':input_text' => $payload['input'],
            ':data_json' => json_encode($payload, JSON_UNESCAPED_UNICODE | JSON_UNESCAPED_SLASHES),
        ]);
    }

    public static function delete(int $id, int $userId): void
    {
        $pdo = Database::getConnection();
        $stmt = $pdo->prepare('DELETE FROM projects WHERE id = ? AND user_id = ?');
        $stmt->execute([$id, $userId]);
    }
}
