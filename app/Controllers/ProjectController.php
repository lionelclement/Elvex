<?php
require_once __DIR__ . '/../Models/Project.php';
require_once __DIR__ . '/../Services/ElvexRunner.php';

class ProjectController
{
    private function requireLogin(): void
    {
        if (!is_logged_in()) {
            flash('error', 'Connecte-toi pour gérer les projets.');
            redirect('');
        }
    }

    private function payload(): array
    {
        return [
            'name' => trim($_POST['name'] ?? ''),
            'macros' => (string)($_POST['macros'] ?? ''),
            'rules' => (string)($_POST['rules'] ?? ''),
            'lexicon' => (string)($_POST['lexicon'] ?? ''),
            'pattern' => (string)($_POST['pattern'] ?? ''),
            'morpho' => (string)($_POST['morpho'] ?? ''),
            'post' => (string)($_POST['post'] ?? ''),
            'input' => (string)($_POST['input'] ?? ''),
        ];
    }

    public function create(): void
    {
        $this->requireLogin();
        require_csrf();

        $payload = $this->payload();
        if ($payload['name'] === '') {
            flash('error', 'Le nom du projet est obligatoire.');
            redirect('');
        }

        $projectId = Project::create((int)current_user()['id'], $payload);
        flash('success', 'Projet créé.');
        redirect('?project=' . $projectId);
    }

    public function update(): void
    {
        $this->requireLogin();
        require_csrf();

        $id = (int)($_POST['id'] ?? 0);
        if ($id <= 0) {
            flash('error', 'Projet invalide.');
            redirect('');
        }

        $payload = $this->payload();
        if ($payload['name'] === '') {
            flash('error', 'Le nom du projet est obligatoire.');
            redirect('?project=' . $id);
        }

        Project::update($id, (int)current_user()['id'], $payload);
        flash('success', 'Projet mis à jour.');
        redirect('?project=' . $id);
    }

    public function delete(): void
    {
        $this->requireLogin();
        require_csrf();

        $id = (int)($_POST['id'] ?? 0);
        if ($id > 0) {
            Project::delete($id, (int)current_user()['id']);
            flash('success', 'Projet supprimé.');
        }

        redirect('');
    }

    public function run(): void
    {
        require_csrf();

        header('Content-Type: application/json; charset=UTF-8');

        try {
            $result = ElvexRunner::run($this->payload());

            http_response_code((($result['exitCode'] ?? 1) === 0) ? 200 : 500);

            echo json_encode([
                'message' => $result['message'] ?? '',
                'exitCode' => $result['exitCode'] ?? 1,
                'output' => $result['output'] ?? '',
                'error' => $result['error'] ?? '',
                'logUrl' => $result['logUrl'] ?? '',
            ], JSON_UNESCAPED_UNICODE);
        } catch (Throwable $e) {
            http_response_code(500);
            echo json_encode([
                'message' => 'Internal error.',
                'exitCode' => 1,
                'output' => '',
                'error' => $e->getMessage(),
                'logUrl' => '',
            ], JSON_UNESCAPED_UNICODE);
        }

        exit;
    }
}