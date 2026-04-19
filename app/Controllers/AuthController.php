<?php
require_once __DIR__ . '/../Models/User.php';
require_once __DIR__ . '/../Services/Mailer.php';

class AuthController
{
    public function signupRequest(): void
    {
        require_csrf();

        $email = trim($_POST['email'] ?? '');
        $displayName = trim($_POST['display_name'] ?? '');
        $password = (string)($_POST['password'] ?? '');
        $passwordConfirm = (string)($_POST['password_confirm'] ?? '');

        if ($email === '' || $displayName === '') {
            flash('error', 'Nom de compte et email sont obligatoires.');
            redirect('');
        }

        if (!filter_var($email, FILTER_VALIDATE_EMAIL)) {
            flash('error', 'Email invalide.');
            redirect('');
        }

        if ($password !== $passwordConfirm) {
            flash('error', 'Les mots de passe ne correspondent pas.');
            redirect('');
        }

        if (!password_is_strong($password)) {
            flash('error', 'Mot de passe trop faible. Il faut au moins 12 caractères avec majuscule, minuscule, chiffre et caractère spécial.');
            redirect('');
        }

        $code = (string)random_int(100000, 999999);
        User::createPending($email, $displayName, $password, $code);

        $sent = Mailer::sendSignupCode($email, $displayName, $code);

        if ($sent) {
            flash('success', 'Code de création envoyé par email.');
        } else {
            flash('success', 'Compte en attente créé, mais l’envoi email a échoué. Vérifie la configuration mail() de PHP.');
        }

        redirect('?show=verify-signup&email=' . urlencode($email));
    }

    public function signupVerify(): void
    {
        require_csrf();

        $email = trim($_POST['email'] ?? '');
        $code = trim($_POST['code'] ?? '');

        if ($email === '' || $code === '') {
            flash('error', 'Email et code sont obligatoires.');
            redirect('');
        }

        $user = User::verifySignupCode($email, $code);
        if (!$user) {
            flash('error', 'Code invalide ou expiré.');
            redirect('?show=verify-signup&email=' . urlencode($email));
        }

        $_SESSION['user'] = [
            'id' => (int)$user['id'],
            'email' => $user['email'],
            'display_name' => $user['display_name'],
        ];

        flash('success', 'Compte créé et connecté.');
        redirect('');
    }

    public function signin(): void
    {
        require_csrf();

        $email = trim($_POST['email'] ?? '');
        $password = (string)($_POST['password'] ?? '');

        if ($email === '' || $password === '') {
            flash('error', 'Email et mot de passe obligatoires.');
            redirect('');
        }

        $user = User::verifyPassword($email, $password);
        if (!$user) {
            flash('error', 'Compte introuvable, non vérifié, ou mot de passe incorrect.');
            redirect('');
        }

        $_SESSION['user'] = [
            'id' => (int)$user['id'],
            'email' => $user['email'],
            'display_name' => $user['display_name'],
        ];

        flash('success', 'Connexion réussie.');
        redirect('');
    }

    public function signout(): void
    {
        require_csrf();
        unset($_SESSION['user']);
        flash('success', 'Déconnecté.');
        redirect('');
    }

    public function passwordRecoveryRequest(): void
    {
        require_csrf();

        $email = trim($_POST['email'] ?? '');
        if ($email === '') {
            flash('error', 'Email obligatoire.');
            redirect('');
        }

        $user = User::findByEmail($email);
        if (!$user || (int)$user['is_verified'] !== 1) {
            flash('error', 'Compte introuvable ou non vérifié.');
            redirect('');
        }

        $code = (string)random_int(100000, 999999);
        User::setPasswordResetToken($email, $code);
        $sent = Mailer::sendPasswordResetCode($email, $user['display_name'], $code);

        if ($sent) {
            flash('success', 'Code de réinitialisation envoyé par email.');
        } else {
            flash('success', 'Code généré, mais l’envoi email a échoué. Vérifie la configuration mail() de PHP.');
        }

        redirect('?show=reset-password&email=' . urlencode($email));
    }

    public function passwordRecoveryConfirm(): void
    {
        require_csrf();

        $email = trim($_POST['email'] ?? '');
        $code = trim($_POST['code'] ?? '');
        $password = (string)($_POST['password'] ?? '');
        $passwordConfirm = (string)($_POST['password_confirm'] ?? '');

        if ($email === '' || $code === '' || $password === '' || $passwordConfirm === '') {
            flash('error', 'Tous les champs sont obligatoires.');
            redirect('?show=reset-password&email=' . urlencode($email));
        }

        if ($password !== $passwordConfirm) {
            flash('error', 'Les mots de passe ne correspondent pas.');
            redirect('?show=reset-password&email=' . urlencode($email));
        }

        if (!password_is_strong($password)) {
            flash('error', 'Mot de passe trop faible. Il faut au moins 12 caractères avec majuscule, minuscule, chiffre et caractère spécial.');
            redirect('?show=reset-password&email=' . urlencode($email));
        }

        if (!User::resetPasswordWithToken($email, $code, $password)) {
            flash('error', 'Code invalide ou expiré.');
            redirect('?show=reset-password&email=' . urlencode($email));
        }

        flash('success', 'Mot de passe mis à jour. Tu peux maintenant te connecter.');
        redirect('');
    }
}
