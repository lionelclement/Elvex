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
                        value="<?= e($selectedProject['name'] ?? '') ?>"
                        <?= !is_logged_in() ? 'readonly' : '' ?>>
                </div>

                <div class="actions">
                    <?php if (is_logged_in() && empty($selectedProject['is_example'])): ?>
                        <button type="submit" class="btn primary">
                            <?= $selectedProject ? 'Save Changes' : 'Create Project' ?>
                        </button>
                    <?php endif; ?>

                    <button type="button" class="btn secondary" id="run-elvex-btn">Run ELVEX</button>

                    <?php if (is_logged_in()): ?>
                        <a class="btn secondary" href="<?= $baseIndexUrl ?>">New Project</a>
                    <?php endif; ?>
                </div>

                <div style="height: 18px;"></div>

                <div class="tabbar">
                    <button type="button" class="tab-btn active" data-tab="macros">Macros</button>
                    <button type="button" class="tab-btn" data-tab="rules">Rules</button>
                    <button type="button" class="tab-btn" data-tab="lexicon">Lexicon</button>
                    <button type="button" class="tab-btn" data-tab="pattern">Pattern</button>
                    <button type="button" class="tab-btn" data-tab="morpho">Morpho</button>
                    <button type="button" class="tab-btn" data-tab="post">PostMorpho</button>
                    <button type="button" class="tab-btn" data-tab="input">Input</button>
                    <button type="button" class="tab-btn" data-tab="output">Output</button>
                    <button type="button" class="tab-btn" data-tab="log">Log</button>
                </div>

                <?php
                function editor($name, $value, $readonly = false) {
                    ?>
                    <div class="tab-panel <?= $name === 'macros' ? 'active' : '' ?>" data-tab="<?= $name ?>">
                        <div class="row">
                            <label><?= ucfirst($name) ?></label>
                            <div class="editor-wrap" data-editor>
                                <div class="line-numbers"></div>
                                <textarea name="<?= $name ?>" <?= $readonly ? 'readonly' : '' ?>><?= e($value ?? '') ?></textarea>
                            </div>
                        </div>
                    </div>
                    <?php
                }

                $ro = !is_logged_in();
                editor('macros', $selectedProject['macros'] ?? '', $ro);
                editor('rules', $selectedProject['rules'] ?? '', $ro);
                editor('lexicon', $selectedProject['lexicon'] ?? '', $ro);
                editor('pattern', $selectedProject['pattern'] ?? '', $ro);
                editor('morpho', $selectedProject['morpho'] ?? '', $ro);
                editor('post', $selectedProject['post_morpho'] ?? '', $ro);
                editor('input', $selectedProject['input_text'] ?? '', $ro);
                ?>

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
    var runBtn = document.getElementById('run-elvex-btn');
    var form = document.getElementById('project-form');
    var output = document.getElementById('elvex-output');
    var error = document.getElementById('elvex-error');
    var logFrame = document.getElementById('elvex-log-frame');

    function activateTab(tabName) {
        document.querySelectorAll('.tab-btn').forEach(b => b.classList.remove('active'));
        document.querySelectorAll('.tab-panel').forEach(p => p.classList.remove('active'));

        document.querySelector('[data-tab="' + tabName + '"].tab-btn').classList.add('active');
        document.querySelector('[data-tab="' + tabName + '"].tab-panel').classList.add('active');
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

    runBtn.addEventListener('click', async function () {
        runBtn.disabled = true;
        runBtn.textContent = 'Executing...';
        output.value = '';
        error.value = '';
        logFrame.innerHTML = '<em>Running...</em>';

        try {
            const formData = new FormData(form);

            const response = await fetch('<?= e(url_path('projects/run')) ?>', {
                method: 'POST',
                body: formData
            });

            const raw = await response.text();

            let data;
            try {
                data = JSON.parse(raw);
            } catch (e) {
                throw new Error(raw);
            }

            output.value = data.output || '';
            error.value = data.error || '';

            if (!response.ok) {
                error.value = data.error || data.message || 'HTTP error';
            }

            await loadLog(data.logUrl || '');
            activateTab('output');

        } catch (e) {
            error.value = e.message;
            activateTab('output');
        } finally {
            runBtn.disabled = false;
            runBtn.textContent = 'Run ELVEX';
        }
    });
})();
</script>

        </div>
    </section>
</div>