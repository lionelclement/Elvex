<?php
$baseIndexUrl = e(url_path(''));
?>

<div class="page-grid">
    <aside>
        <?php
        $exampleProjects = [];
        $userProjects = [];

        foreach ($projects as $project) {
            if (!empty($project['is_example'])) {
                $exampleProjects[] = $project;
            } else {
                $userProjects[] = $project;
            }
        }
        ?>

        <?php
        $projectInputs = [];
        if ($selectedProject) {
            foreach (preg_split('/\R/', (string)($selectedProject['input_text'] ?? '')) as $line) {
                $line = trim($line);
                if ($line === '' || str_starts_with($line, '//')) {
                    continue;
                }
                $projectInputs[$line] = $line;
            }
        }
        $projectInputs = array_values($projectInputs);
        $initialServerInput = $projectInputs[0] ?? '';
        ?>

        <?php if (is_logged_in()): ?>
            <div class="card" style="margin-bottom:16px;">
                <div class="card-header">My Projects</div>
                <div class="card-body">
                    <?php if (empty($userProjects)): ?>
                        <p class="hint">No projects at the moment.</p>
                    <?php else: ?>
                        <ul class="project-list">
                            <?php foreach ($userProjects as $project): ?>
                                <li>
                                    <a href="<?= $baseIndexUrl ?>?project=<?= urlencode((string)$project['id']) ?>"
                                       class="<?= ($selectedProject && (string)$selectedProject['id'] === (string)$project['id']) ? 'active' : '' ?>">
                                        <?= e($project['name']) ?>
                                    </a>
                                </li>
                            <?php endforeach; ?>
                        </ul>
                    <?php endif; ?>
                </div>
            </div>
        <?php endif; ?>

        <div class="card">
            <div class="card-header">Example Projects</div>
            <div class="card-body">
                <?php if (empty($exampleProjects)): ?>
                    <p class="hint">No example projects available.</p>
                <?php else: ?>
                    <ul class="project-list">
                        <?php foreach ($exampleProjects as $project): ?>
                            <li>
                                <a href="<?= $baseIndexUrl ?>?project=<?= urlencode((string)$project['id']) ?>"
                                   class="<?= ($selectedProject && (string)$selectedProject['id'] === (string)$project['id']) ? 'active' : '' ?>">
                                    <?= e($project['name']) ?>
                                </a>
                            </li>
                        <?php endforeach; ?>
                    </ul>
                <?php endif; ?>
            </div>
        </div>
    </aside>

    <section class="card">
        <div class="card-header"><?= $selectedProject ? 'Modify Project' : 'Create Project' ?></div>
        <div class="card-body">

            <form id="project-form" method="post" action="<?= e(url_path($selectedProject && empty($selectedProject['is_example']) ? 'projects/update' : 'projects/create')) ?>" data-tabs-container>
                <input type="hidden" name="_csrf" value="<?= e(csrf_token()) ?>">

                <?php if ($selectedProject && empty($selectedProject['is_example'])): ?>
                    <input type="hidden" name="id" value="<?= (int)$selectedProject['id'] ?>">
                <?php endif; ?>

                <div class="row">
                    <label>Project Name</label>
                    <input type="text" name="name"
                       value="<?= e($selectedProject['name'] ?? '') ?>">
                </div>

                <div class="actions">
                    <?php if (is_logged_in() && empty($selectedProject['is_example'])): ?>
                        <button type="submit" class="btn primary">
                            <?= $selectedProject ? 'Save Changes' : 'Create Project' ?>
                        </button>
                    <?php endif; ?>

                    <button type="button" class="btn secondary" id="run-elvex-btn">Run once</button>
                    <button type="button" class="btn server-toggle server-toggle-start" id="toggle-elvex-server-btn" data-running="0">Start server</button>
                    <span id="elvex-server-status" class="hint">Server stopped</span>

                    <?php if (is_logged_in()): ?>
                        <a class="btn secondary" href="<?= $baseIndexUrl ?>">New Project</a>
                    <?php endif; ?>
                </div>

                <div style="height: 18px;"></div>

                <div class="tabbar">
                    <button type="button" class="tab-btn active" data-tab="input">Input</button>
                    <button type="button" class="tab-btn" data-tab="macros">Macros</button>
                    <button type="button" class="tab-btn" data-tab="rules">Rules</button>
                    <button type="button" class="tab-btn" data-tab="lexicon">Lexicon</button>
                    <button type="button" class="tab-btn" data-tab="pattern">Lexicon Patterns</button>
                    <button type="button" class="tab-btn" data-tab="morpho">Morphology</button>
                    <button type="button" class="tab-btn" data-tab="post">Orthographic Rules</button>
                    <button type="button" class="tab-btn" data-tab="output">Output</button>
                    <button type="button" class="tab-btn" data-tab="log">Log</button>
                </div>

                <?php
                function editor($name, $value, $readonly = false, $active = false, $label = null) {
                    $commonToolbar = [
                        ['label' => '⇥', 'insert' => "\t"],
                    ];

                    $toolbars = [
                        'rules' => array_merge($commonToolbar, [
                            ['label' => '→', 'insert' => '→'],
                            ['label' => '↑', 'insert' => '↑'],
                            ['label' => '↓', 'insert' => '↓'],
                            ['label' => '⇑', 'insert' => '⇑'],
                            ['label' => '⇓', 'insert' => '⇓'],
                            ['label' => '⊂', 'insert' => '⊂'],
                            ['label' => '∪', 'insert' => '∪'],
                            ['label' => '|', 'insert' => '|'],
                            ['label' => '≤', 'insert' => '≤'],
                            ['label' => '≥', 'insert' => '≥'],
                            ['label' => '≠', 'insert' => '≠'],
                            ['label' => '⇔', 'insert' => '⇔'],
                            ['label' => '¬', 'insert' => '¬'],
                        ]),
                        'pattern' => $commonToolbar,
                        'morpho' => $commonToolbar,
                    ];

                    $toolbarButtons = $toolbars[$name] ?? [];
                    ?>
                    <div class="tab-panel <?= $active ? 'active' : '' ?>" data-tab="<?= $name ?>">
                        <div class="row">
                            <label><?= e($label ?? ucfirst($name)) ?></label>
                            <?php if (!empty($toolbarButtons)): ?>
                                <div class="symbol-toolbar">
                                    <?php foreach ($toolbarButtons as $button): ?>
                                        <button type="button" data-insert="<?= e($button['insert']) ?>" title="Insert <?= e($button['label']) ?>">
                                            <?= e($button['label']) ?>
                                        </button>
                                    <?php endforeach; ?>
                                </div>
                            <?php endif; ?>
                            <div class="editor-wrap" data-editor>
                                <div class="line-numbers"></div>
                                <textarea name="<?= $name ?>" <?= $readonly ? 'readonly' : '' ?>><?= e($value ?? '') ?></textarea>
                            </div>
                        </div>
                    </div>
                    <?php
                }

                editor('input', $selectedProject['input_text'] ?? '', false, true, 'Input');
                editor('macros', $selectedProject['macros'] ?? '', false, false, 'Macros');
                editor('rules', $selectedProject['rules'] ?? '', false, false, 'Rules');
                editor('lexicon', $selectedProject['lexicon'] ?? '', false, false, 'Lexicon');
                editor('pattern', $selectedProject['pattern'] ?? '', false, false, 'Lexicon Patterns');
                editor('morpho', $selectedProject['morpho'] ?? '', false, false, 'Morphology');
                editor('post', $selectedProject['post_morpho'] ?? '', false, false, 'Orthographic Rules');
                ?>

                <div id="elvex-server-input-panel" class="card" style="margin: 0 0 16px 0; border:1px solid #cfd8e3;">
                    <div class="card-body">
                        <div class="row">
                            <label>Server input</label>
                            <input type="text" id="elvex-server-input" value="<?= e($initialServerInput) ?>" placeholder="One input line, e.g. the girl looks after the child">
                            <div class="actions" style="margin-top:8px;">
                                <button type="button" class="btn secondary" id="send-elvex-input-btn" disabled>Send input</button>
                                <span class="hint">Start the server, then send inputs one by one. The field stays available while you edit the project.</span>
                            </div>
                        </div>

                        <div class="row" style="margin-top:12px;">
                            <label>Example inputs from this project</label>
                            <div id="example-inputs-list" style="display:flex; flex-direction:column; gap:8px;">
                                <?php foreach ($projectInputs as $projectInput): ?>
                                    <button type="button" class="btn secondary" data-example-input="<?= e($projectInput) ?>" style="text-align:left; white-space:normal;">
                                        <code><?= e($projectInput) ?></code>
                                    </button>
                                <?php endforeach; ?>
                            </div>
                            <p class="hint" style="margin-top:8px;">These are the non-commented lines from the Input tab. Edit Input to change this list.</p>
                        </div>
                    </div>
                </div>

                <div class="tab-panel" data-tab="output">
                    <div class="row">
                        <label>Output</label>
                        <textarea id="elvex-output" readonly></textarea>
                    </div>
                    <div class="row">
                        <label>Error</label>
                        <textarea id="elvex-error" readonly></textarea>
                    </div>
                </div>

                <div class="tab-panel" data-tab="log">
                    <div class="row">
                        <label>Trace</label>
                        <div id="elvex-log-frame" style="border:1px solid #cfd8e3; border-radius:10px; min-height:400px; padding:10px;">
                            <em class="hint">No trace available.</em>
                        </div>
                    </div>
                </div>

            </form>

<?php if (is_logged_in() && $selectedProject && empty($selectedProject['is_example'])): ?>
    <div style="margin-top:14px;">
        <button type="button" class="btn danger" data-open-modal="delete-project-modal">
            Delete Project
        </button>
    </div>

    <div id="delete-project-modal" class="modal-backdrop">
        <div class="modal">
            <div class="modal-header">Delete Project</div>
            <div class="modal-body">
                Are you sure you want to delete
                <strong><?= e($selectedProject['name']) ?></strong>?
                This action cannot be undone.
            </div>
            <div class="modal-footer">
                <button type="button" class="btn secondary" data-close-modal>Cancel</button>
                <form method="post" action="<?= e(url_path('projects/delete')) ?>" style="margin:0;">
                    <input type="hidden" name="_csrf" value="<?= e(csrf_token()) ?>">
                    <input type="hidden" name="id" value="<?= (int)$selectedProject['id'] ?>">
                    <button type="submit" class="btn danger">Delete</button>
                </form>
            </div>
        </div>
    </div>
<?php endif; ?>

<script>
(function () {
    var form = document.getElementById('project-form');
    var runBtn = document.getElementById('run-elvex-btn');
    var toggleServerBtn = document.getElementById('toggle-elvex-server-btn');
    var serverRunning = false;
    var sendBtn = document.getElementById('send-elvex-input-btn');
    var statusLabel = document.getElementById('elvex-server-status');
    var serverInput = document.getElementById('elvex-server-input');
    var serverInputPanel = document.getElementById('elvex-server-input-panel');
    var inputTextarea = form ? form.querySelector('textarea[name="input"]') : null;
    var exampleInputsList = document.getElementById('example-inputs-list');
    var output = document.getElementById('elvex-output');
    var error = document.getElementById('elvex-error');
    var logFrame = document.getElementById('elvex-log-frame');

    function activateTab(tabName) {
        document.querySelectorAll('.tab-btn').forEach(b => b.classList.remove('active'));
        document.querySelectorAll('.tab-panel').forEach(p => p.classList.remove('active'));

        var btn = document.querySelector('[data-tab="' + tabName + '"].tab-btn');
        var panel = document.querySelector('[data-tab="' + tabName + '"].tab-panel');
        if (btn) btn.classList.add('active');
        if (panel) panel.classList.add('active');
    }

    function setServerUi(running, message) {
        serverRunning = !!running;
        if (toggleServerBtn) {
            toggleServerBtn.disabled = false;
            toggleServerBtn.dataset.running = serverRunning ? '1' : '0';
            toggleServerBtn.textContent = serverRunning ? 'Stop server' : 'Start server';
            toggleServerBtn.classList.toggle('server-toggle-start', !serverRunning);
            toggleServerBtn.classList.toggle('server-toggle-stop', serverRunning);
        }
        if (sendBtn) sendBtn.disabled = !serverRunning;
        if (serverInputPanel) serverInputPanel.style.display = '';
        if (statusLabel) statusLabel.textContent = message || (serverRunning ? 'Server running' : 'Server stopped');
    }

    async function parseJsonResponse(response) {
        const raw = await response.text();
        try {
            return JSON.parse(raw);
        } catch (e) {
            throw new Error(raw);
        }
    }

    async function postForm(url, extra) {
        const formData = new FormData(form);
        if (extra) {
            Object.keys(extra).forEach(function (key) {
                formData.set(key, extra[key]);
            });
        }

        const response = await fetch(url, {
            method: 'POST',
            body: formData
        });

        const data = await parseJsonResponse(response);
        if (!response.ok) {
            throw new Error(data.error || data.message || 'HTTP error');
        }
        return data;
    }

    async function loadLog(url) {
        if (!url) return;
        try {
            const res = await fetch(url);
            logFrame.innerHTML = await res.text();
        } catch (e) {
            logFrame.innerHTML = '<pre>' + e.message + '</pre>';
        }
    }

    async function refreshServerStatus() {
        try {
            const response = await fetch('<?= e(url_path('projects/server/status')) ?>');
            const data = await parseJsonResponse(response);
            setServerUi(!!data.running, data.running ? 'Server running' : 'Server stopped');
        } catch (e) {
            setServerUi(false, 'Server status unavailable');
        }
    }

    runBtn.addEventListener('click', async function () {
        runBtn.disabled = true;
        runBtn.textContent = 'Executing...';
        output.value = '';
        error.value = '';
        logFrame.innerHTML = '<em>Running...</em>';

        try {
            const data = await postForm('<?= e(url_path('projects/run')) ?>');
            output.value = data.output || '';
            error.value = data.error || '';
            await loadLog(data.logUrl || '');
            activateTab('output');
        } catch (e) {
            error.value = e.message;
            activateTab('output');
        } finally {
            runBtn.disabled = false;
            runBtn.textContent = 'Run once';
        }
    });

    async function startServer() {
        toggleServerBtn.disabled = true;
        toggleServerBtn.textContent = 'Starting...';
        output.value = '';
        error.value = '';
        logFrame.innerHTML = '<em>No trace available.</em>';
        if (statusLabel) statusLabel.textContent = 'Starting server...';

        try {
            const data = await postForm('<?= e(url_path('projects/server/start')) ?>');
            setServerUi(true, data.message || 'Server running');
            output.value = (data.command ? 'Command: ' + data.command + '\n' : '') + 'Server ready. Send inputs one by one.';
            activateTab('output');
        } catch (e) {
            setServerUi(false, 'Server stopped');
            error.value = e.message;
            activateTab('output');
        }
    }

    async function stopServer() {
        toggleServerBtn.disabled = true;
        toggleServerBtn.textContent = 'Stopping...';
        if (statusLabel) statusLabel.textContent = 'Stopping server...';

        try {
            const data = await postForm('<?= e(url_path('projects/server/stop')) ?>');
            setServerUi(false, data.message || 'Server stopped');
        } catch (e) {
            error.value = e.message;
            activateTab('output');
            await refreshServerStatus();
        }
    }

    toggleServerBtn.addEventListener('click', async function () {
        if (serverRunning) {
            await stopServer();
        } else {
            await startServer();
        }
    });

    sendBtn.addEventListener('click', async function () {
        const value = (serverInput.value || '').trim();
        if (!value) {
            error.value = 'Empty input.';
            activateTab('output');
            return;
        }

        sendBtn.disabled = true;
        error.value = '';

        try {
            const data = await postForm('<?= e(url_path('projects/server/send')) ?>', {server_input: value});
            output.value = data.output || '';
            setServerUi(!!data.running, data.running ? 'Server running' : 'Server stopped');
            activateTab('output');
        } catch (e) {
            error.value = e.message;
            activateTab('output');
            await refreshServerStatus();
        } finally {
            if (serverRunning) {
                sendBtn.disabled = false;
            }
        }
    });

    function extractExampleInputs(text) {
        var seen = {};
        var values = [];
        (text || '').split(/\r?\n/).forEach(function (line) {
            var value = line.trim();
            if (!value || value.indexOf('//') === 0 || seen[value]) return;
            seen[value] = true;
            values.push(value);
        });
        return values;
    }

    function renderExampleInputs() {
        if (!exampleInputsList || !inputTextarea) return;
        var values = extractExampleInputs(inputTextarea.value);
        exampleInputsList.innerHTML = '';

        if (values.length === 0) {
            var empty = document.createElement('p');
            empty.className = 'hint';
            empty.textContent = 'No non-commented input lines yet.';
            exampleInputsList.appendChild(empty);
            return;
        }

        values.forEach(function (value) {
            var button = document.createElement('button');
            button.type = 'button';
            button.className = 'btn secondary';
            button.setAttribute('data-example-input', value);
            button.style.textAlign = 'left';
            button.style.whiteSpace = 'normal';

            var code = document.createElement('code');
            code.textContent = value;
            button.appendChild(code);
            exampleInputsList.appendChild(button);
        });
    }

    if (exampleInputsList) {
        exampleInputsList.addEventListener('click', function (event) {
            var button = event.target.closest('[data-example-input]');
            if (!button || !serverInput) return;
            serverInput.value = button.getAttribute('data-example-input') || '';
            serverInput.focus();
        });
    }

    if (inputTextarea) {
        inputTextarea.addEventListener('input', renderExampleInputs);
        renderExampleInputs();
    }

    serverInput.addEventListener('keydown', function (event) {
        if (event.key === 'Enter' && !event.shiftKey) {
            event.preventDefault();
            if (!sendBtn.disabled) {
                sendBtn.click();
            }
        }
    });

    refreshServerStatus();
})();
</script>

        </div>
    </section>
</div>