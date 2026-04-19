<?php
class Database
{
    private static ?PDO $pdo = null;

    public static function getConnection(): PDO
    {
        if (self::$pdo === null) {
            $db = config()['db'];
            $dsn = sprintf(
                'mysql:host=%s;dbname=%s;charset=%s',
                $db['host'],
                $db['name'],
                $db['charset']
            );

            self::$pdo = new PDO($dsn, $db['user'], $db['pass'], [
                PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION,
                PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC,
            ]);
        }

        return self::$pdo;
    }
}
