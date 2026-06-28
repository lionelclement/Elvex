<?php
require_once __DIR__ . '/../Models/Project.php';
require_once __DIR__ . '/../Services/ElvexRunner.php';

class ProjectController
{
    private function requireLogin(): void
    {
        if (!is_logged_in()) {
            flash('error', 'Sign in to manage projects.');
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
            flash('error', 'Project name is required.');
            redirect('');
        }

        $projectId = Project::create((int)current_user()['id'], $payload);
        flash('success', 'Project created.');
        redirect('?project=' . $projectId);
    }

    public function update(): void
    {
        $this->requireLogin();
        require_csrf();

        $id = (int)($_POST['id'] ?? 0);
        if ($id <= 0) {
            flash('error', 'Invalid project.');
            redirect('');
        }

        $payload = $this->payload();
        if ($payload['name'] === '') {
            flash('error', 'Project name is required.');
            redirect('?project=' . $id);
        }

        Project::update($id, (int)current_user()['id'], $payload);
        flash('success', 'Project updated.');
        redirect('?project=' . $id);
    }

    public function delete(): void
    {
        $this->requireLogin();
        require_csrf();

        $id = (int)($_POST['id'] ?? 0);
        if ($id > 0) {
            Project::delete($id, (int)current_user()['id']);
            flash('success', 'Project deleted.');
        }

        redirect('');
    }


    private function jsonResponse(array $payload, int $status = 200): void
    {
        header('Content-Type: application/json; charset=UTF-8');
        http_response_code($status);
        echo json_encode($payload, JSON_UNESCAPED_UNICODE);
        exit;
    }

    public function serverStart(): void
    {
        require_csrf();

        try {
            $this->jsonResponse(ElvexRunner::startServer($this->payload()));
        } catch (Throwable $e) {
            $this->jsonResponse([
                'message' => 'Error starting the Elvex server.',
                'running' => false,
                'error' => $e->getMessage(),
            ], 500);
        }
    }

    public function serverStop(): void
    {
        require_csrf();

        try {
            $this->jsonResponse(ElvexRunner::stopServer());
        } catch (Throwable $e) {
            $this->jsonResponse([
                'message' => 'Error stopping the Elvex server.',
                'running' => false,
                'error' => $e->getMessage(),
            ], 500);
        }
    }

    public function serverSend(): void
    {
        require_csrf();

        try {
            $input = (string)($_POST['server_input'] ?? $_POST['input'] ?? '');
            $this->jsonResponse(ElvexRunner::sendToServer($input));
        } catch (Throwable $e) {
            $this->jsonResponse([
                'message' => 'Error while processing the input.',
                'running' => false,
                'output' => '',
                'error' => $e->getMessage(),
            ], 500);
        }
    }

    public function serverStatus(): void
    {
        try {
            $this->jsonResponse(ElvexRunner::serverStatus());
        } catch (Throwable $e) {
            $this->jsonResponse([
                'running' => false,
                'error' => $e->getMessage(),
            ], 500);
        }
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