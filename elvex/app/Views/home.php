<?php
$baseIndexUrl = e(url_path(''));
?>

<style>
.editor-wrap.show-invisibles {
    position: relative;
}

.editor-wrap.show-invisibles .editor-ghost,
.editor-wrap.show-invisibles textarea {
    font: inherit;
    line-height: inherit;
    letter-spacing: inherit;
    tab-size: 4;
    -moz-tab-size: 4;
    white-space: pre;
    word-wrap: normal;
    overflow: auto;
    box-sizing: border-box;
}

.editor-wrap.show-invisibles .editor-ghost {
    position: absolute;
    inset: 0;
    pointer-events: none;
    z-index: 1;
    color: #94a3b8;
    background: transparent;
    margin: 0;
    padding: inherit;
    border: 0;
}

.editor-wrap.show-invisibles textarea {
    position: relative;
    z-index: 2;
    background: transparent;
    color: transparent;
    caret-color: #111827;
}

.editor-wrap.show-invisibles textarea::selection {
    background: rgba(59, 130, 246, 0.25);
}

.editor-wrap.show-invisibles textarea::-moz-selection {
    background: rgba(59, 130, 246, 0.25);
}

.editor-wrap.show-invisibles .ch-tab,
.editor-wrap.show-invisibles .ch-space,
.editor-wrap.show-invisibles .ch-eol {
    color: #94a3b8;
}
</style>

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
                       value="<?= e($selectedProject['name'] ?? '') ?>">
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

                    $showInvisibles = in_array($name, ['pattern', 'morpho'], true);
                    $toolbarButtons = $toolbars[$name] ?? [];
                    ?>
                    <div class="tab-panel <?= $name === 'macros' ? 'active' : '' ?>" data-tab="<?= $name ?>">
                        <div class="row">
                            <label><?= ucfirst($name) ?></label>
                            <?php if (!empty($toolbarButtons)): ?>
                                <div class="symbol-toolbar">
                                    <?php foreach ($toolbarButtons as $button): ?>
                                        <button type="button" data-insert="<?= e($button['insert']) ?>" title="Insert <?= e($button['label']) ?>">
                                            <?= e($button['label']) ?>
                                        </button>
                                    <?php endforeach; ?>
                                </div>
                            <?php endif; ?>
                            <div class="editor-wrap <?= $showInvisibles ? 'show-invisibles' : '' ?>" data-editor>
                                <div class="line-numbers"></div>
                                <?php if ($showInvisibles): ?>
                                    <pre class="editor-ghost" aria-hidden="true"></pre>
                                <?php endif; ?>
                                <textarea
                                    name="<?= $name ?>"
                                    <?= $readonly ? 'readonly' : '' ?>
                                    <?= $showInvisibles ? 'data-show-invisibles="1"' : '' ?>
                                ><?= e($value ?? '') ?></textarea>
                            </div>
                        </div>
                    </div>
                    <?php
                }

                editor('macros', $selectedProject['macros'] ?? '', false);
                editor('rules', $selectedProject['rules'] ?? '', false);
                editor('lexicon', $selectedProject['lexicon'] ?? '', false);
                editor('pattern', $selectedProject['pattern'] ?? '', false);
                editor('morpho', $selectedProject['morpho'] ?? '', false);
                editor('post', $selectedProject['post_morpho'] ?? '', false);
                editor('input', $selectedProject['input_text'] ?? '', false);
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
        document.querySelectorAll('.tab-btn').forEach(function (b) {
            b.classList.remove('active');
        });
        document.querySelectorAll('.tab-panel').forEach(function (p) {
            p.classList.remove('active');
        });

        var btn = document.querySelector('[data-tab="' + tabName + '"].tab-btn');
        var panel = document.querySelector('[data-tab="' + tabName + '"].tab-panel');

        if (btn) btn.classList.add('active');
        if (panel) panel.classList.add('active');
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

    function escapeHtml(s) {
        return s
            .replace(/&/g, '&amp;')
            .replace(/</g, '&lt;')
            .replace(/>/g, '&gt;');
    }

    function renderVisibleChars(text) {
        var escaped = escapeHtml(text);
        escaped = escaped.replace(/\t/g, '<span class="ch-tab">⇥</span>');
        escaped = escaped.replace(/ /g, '<span class="ch-space">·</span>');
        escaped = escaped.replace(/\n/g, '<span class="ch-eol">¶</span>\n');

        if (escaped.endsWith('\n')) {
            return escaped + ' ';
        }

        return escaped;
    }

    function syncGhost(wrap) {
        var textarea = wrap.querySelector('textarea[data-show-invisibles="1"]');
        var ghost = wrap.querySelector('.editor-ghost');

        if (!textarea || !ghost) return;

        ghost.innerHTML = renderVisibleChars(textarea.value);
        ghost.scrollTop = textarea.scrollTop;
        ghost.scrollLeft = textarea.scrollLeft;

        var style = window.getComputedStyle(textarea);
        ghost.style.paddingTop = style.paddingTop;
        ghost.style.paddingRight = style.paddingRight;
        ghost.style.paddingBottom = style.paddingBottom;
        ghost.style.paddingLeft = style.paddingLeft;
        ghost.style.font = style.font;
        ghost.style.lineHeight = style.lineHeight;
        ghost.style.letterSpacing = style.letterSpacing;
        ghost.style.borderRadius = style.borderRadius;
    }

    document.querySelectorAll('.editor-wrap.show-invisibles').forEach(function (wrap) {
        var textarea = wrap.querySelector('textarea[data-show-invisibles="1"]');
        if (!textarea) return;

        syncGhost(wrap);

        textarea.addEventListener('input', function () {
            syncGhost(wrap);
        });

        textarea.addEventListener('scroll', function () {
            syncGhost(wrap);
        });

        window.addEventListener('resize', function () {
            syncGhost(wrap);
        });
    });

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