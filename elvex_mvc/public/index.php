<?php
session_start();

require_once __DIR__ . '/../app/Core/helpers.php';
require_once __DIR__ . '/../app/Core/Database.php';
require_once __DIR__ . '/../app/Core/View.php';
require_once __DIR__ . '/../app/Controllers/HomeController.php';
require_once __DIR__ . '/../app/Controllers/AuthController.php';
require_once __DIR__ . '/../app/Controllers/ProjectController.php';

$route = trim($_GET['route'] ?? '', '/');
$method = $_SERVER['REQUEST_METHOD'] ?? 'GET';

$home = new HomeController();
$auth = new AuthController();
$projects = new ProjectController();

if ($method === 'GET' && $route === '') { $home->index(); exit; }
if ($method === 'GET' && $route === '') { $home->index(); exit; }
if ($method === 'GET' && $route === 'home') { $home->home(); exit; }
if ($method === 'GET' && $route === 'documentation') { $home->documentation(); exit; }if ($method === 'POST' && $route === 'signup/request') { $auth->signupRequest(); exit; }
if ($method === 'POST' && $route === 'signup/verify') { $auth->signupVerify(); exit; }
if ($method === 'POST' && $route === 'signin') { $auth->signin(); exit; }
if ($method === 'POST' && $route === 'signout') { $auth->signout(); exit; }
if ($method === 'POST' && $route === 'password/recovery/request') { $auth->passwordRecoveryRequest(); exit; }
if ($method === 'POST' && $route === 'password/recovery/confirm') { $auth->passwordRecoveryConfirm(); exit; }
if ($method === 'POST' && $route === 'projects/create') { $projects->create(); exit; }
if ($method === 'POST' && $route === 'projects/update') { $projects->update(); exit; }
if ($method === 'POST' && $route === 'projects/delete') { $projects->delete(); exit; }
if ($method === 'POST' && $route === 'projects/run') { $projects->run(); exit; }

http_response_code(404);
echo '404';
