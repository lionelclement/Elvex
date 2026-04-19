<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <title>ELVEX</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
        :root { --bg:#f6f7fb; --card:#ffffff; --text:#1e2430; --muted:#667085; --line:#dde3ec; --brand:#1f4ed8; --brand-dark:#1639a0; --danger:#b42318; --ok:#027a48; }
        * { box-sizing:border-box; }
        body { margin:0; font-family:Arial,sans-serif; background:var(--bg); color:var(--text); }
        .topbar { background:#111827; color:#fff; padding:0 20px; display:flex; align-items:center; justify-content:space-between; min-height:64px; gap:16px; }
        .brand { font-size:20px; font-weight:700; }
        .menu, .auth-menu { display:flex; align-items:center; gap:12px; }
        .menu a, .auth-menu a, .auth-menu button { color:#fff; text-decoration:none; background:transparent; border:1px solid rgba(255,255,255,.2); border-radius:8px; padding:8px 12px; cursor:pointer; font-size:14px; }
        .auth-menu .account-name { padding:8px 12px; background:rgba(255,255,255,.1); border-radius:8px; font-weight:600; }
        .submenu { background:#fff; border-bottom:1px solid var(--line); padding:10px 20px; display:flex; gap:10px; flex-wrap:wrap; }
        .submenu a { text-decoration:none; color:var(--text); padding:8px 10px; border-radius:8px; }
        .submenu a:hover { background:#eef2ff; color:var(--brand); }
        .wrap { max-width:1280px; margin:24px auto; padding:0 16px; }
        .flash { border-radius:10px; padding:12px 14px; margin-bottom:16px; }
        .flash.error { background:#fef3f2; color:var(--danger); border:1px solid #fecdca; }
        .flash.success { background:#ecfdf3; color:var(--ok); border:1px solid #abefc6; }
        .page-grid { display:grid; grid-template-columns:280px 1fr; gap:20px; }
        .card { background:var(--card); border:1px solid var(--line); border-radius:14px; box-shadow:0 1px 2px rgba(16,24,40,.06); }
        .card-header { padding:16px 18px; border-bottom:1px solid var(--line); font-weight:700; }
        .card-body { padding:16px 18px; }
        .project-list { list-style:none; padding:0; margin:0; }
        .project-list li + li { margin-top:8px; }
        .project-list a { display:block; padding:10px 12px; border-radius:10px; text-decoration:none; color:var(--text); border:1px solid transparent; }
        .project-list a.active, .project-list a:hover { background:#eef2ff; border-color:#c7d7fe; color:var(--brand-dark); }
        form .row { margin-bottom:14px; }
        label { display:block; margin-bottom:6px; font-size:14px; color:var(--muted); font-weight:600; }
        input[type=text], input[type=email], input[type=password], textarea {
            width:100%; border:1px solid #cfd8e3; border-radius:10px; padding:10px 12px; font:inherit; background:#fff;
        }
        textarea {
            min-height:180px;
            resize:vertical;
            font-family:Consolas, monospace;
            line-height:1.4;
            white-space:pre;
            overflow-x:auto;
            overflow-y:auto;
            word-wrap:normal;
            overflow-wrap:normal;
        }
        .tabbar { display:flex; flex-wrap:wrap; gap:8px; margin-bottom:14px; }
        .tab-btn { border:1px solid #cfd8e3; background:#fff; border-radius:999px; padding:8px 12px; cursor:pointer; }
        .tab-btn.active { background:#eef2ff; color:var(--brand-dark); border-color:#c7d7fe; }
        .tab-panel { display:none; }
        .tab-panel.active { display:block; }

        .actions { display:flex; gap:10px; flex-wrap:wrap; }
        .btn { border:none; border-radius:10px; padding:10px 14px; cursor:pointer; font-weight:600; text-decoration:none; display:inline-block; }
        .btn.primary { background:var(--brand); color:#fff; }
        .btn.secondary { background:#eef2ff; color:var(--brand-dark); }
        .btn.danger { background:#fef3f2; color:var(--danger); }

        .modal-backdrop { position:fixed; inset:0; background:rgba(15,23,42,.55); display:none; align-items:center; justify-content:center; padding:16px; }
        .modal-backdrop.open { display:flex; }
        .modal { width:100%; max-width:460px; background:#fff; border-radius:14px; border:1px solid var(--line); overflow:hidden; }
        .modal-header, .modal-body, .modal-footer { padding:16px 18px; }
        .modal-header { border-bottom:1px solid var(--line); font-weight:700; }
        .modal-footer { border-top:1px solid var(--line); display:flex; gap:10px; justify-content:flex-end; }
        .hint { color:var(--muted); font-size:13px; }

        .editor-wrap {
            display: flex;
            align-items: stretch;
            border: 1px solid #cfd8e3;
            border-radius: 10px;
            overflow: hidden;
            background: #fff;
        }

        .line-numbers {
            flex: 0 0 56px;
            text-align: right;
            color: #667085;
            background: #f8fafc;
            border-right: 1px solid #e5e7eb;
            font-family: Consolas, monospace;
            font-size: 14px;
            line-height: 1.4;
            overflow: hidden;
            user-select: none;
            position: relative;
        }

        .line-numbers-content {
            padding: 10px 8px;
            white-space: pre;
            will-change: transform;
        }

        .editor-wrap textarea {
            border: 0;
            border-radius: 0;
            margin: 0;
            resize: vertical;
            min-height: 180px;
            height: auto;
            font-family: Consolas, monospace;
            font-size: 14px;
            line-height: 1.4;
            white-space: pre;
            overflow-x: auto;
            overflow-y: auto;
            word-wrap: normal;
            overflow-wrap: normal;
            box-sizing: border-box;
        }
        
        .editor-wrap textarea:focus {
            outline: none;
        }

        .symbol-toolbar {
            display: flex;
            align-items: center;
            gap: 6px;
            margin-bottom: 6px;
            flex-wrap: wrap;
        }

        .symbol-group {
            display: flex;
            gap: 6px;
            flex-wrap: wrap;
        }

        .symbol-separator {
            width: 12px;
        }

        .symbol-toolbar button {
            border: 1px solid #cfd8e3;
            background: #fff;
            border-radius: 6px;
            padding: 4px 8px;
            cursor: pointer;
            font-size: 14px;
        }

        .symbol-toolbar button:hover {
            background: #eef2ff;
        }

        .markdown-body {
            line-height: 1.6;
            font-size: 16px;
        }

        .markdown-body h1,
        .markdown-body h2,
        .markdown-body h3 {
            margin-top: 1.4em;
            margin-bottom: 0.6em;
        }

        .markdown-body p,
        .markdown-body ul,
        .markdown-body ol {
            margin-bottom: 1em;
        }

        .markdown-body code {
            font-family: Consolas, monospace;
            background: #f3f4f6;
            padding: 2px 6px;
            border-radius: 6px;
        }

        .markdown-body pre {
            background: #0f172a;
            color: #e5e7eb;
            padding: 12px;
            border-radius: 10px;
            overflow: auto;
        }

        .markdown-body pre code {
            background: transparent;
            padding: 0;
        }

        .markdown-body a {
            color: var(--brand);
        }

        .markdown-body table {
            border-collapse: collapse;
            width: 100%;
        }

        .markdown-body th,
        .markdown-body td {
            border: 1px solid var(--line);
            padding: 8px;
        }

        @media (max-width:960px){ .page-grid{grid-template-columns:1fr;} .topbar{flex-wrap:wrap; padding-top:12px; padding-bottom:12px;} }
    </style>
</head>
<body>
<header class="topbar">
    <div class="brand">ELVEX</div>

    <nav class="menu">
        <a href="<?= e(url_path('')) ?>">Projects</a>
        <a href="<?= e(url_path('home')) ?>">Home</a>
        <a href="<?= e(url_path('documentation')) ?>">Documentation</a>
    </nav>

    <div class="auth-menu">
        <?php if (is_logged_in()): ?>
            <span class="account-name"><?= e(current_user()['display_name']) ?></span>
            <form method="post" action="<?= e(url_path('signout')) ?>" style="margin:0;">
                <input type="hidden" name="_csrf" value="<?= e(csrf_token()) ?>">
                <button type="submit">Sign out</button>
            </form>
        <?php else: ?>
            <button type="button" data-open-modal="signup-modal">Sign up</button>
            <button type="button" data-open-modal="signin-modal">Sign in</button>
        <?php endif; ?>
    </div>
</header>

<main class="wrap">
    <?php if ($msg = flash('error')): ?><div class="flash error"><?= e($msg) ?></div><?php endif; ?>
    <?php if ($msg = flash('success')): ?><div class="flash success"><?= e($msg) ?></div><?php endif; ?>
    <?= $content ?>
</main>

<?php require __DIR__ . '/../partials/auth_modals.php'; ?>

<script>
document.querySelectorAll('[data-open-modal]').forEach(function(btn) {
    btn.addEventListener('click', function(e) {
        if (btn.tagName.toLowerCase() === 'a') e.preventDefault();
        var parentId = btn.getAttribute('data-close-parent-modal');
        if (parentId) {
            var parentModal = document.getElementById(parentId);
            if (parentModal) parentModal.classList.remove('open');
        }
        var id = btn.getAttribute('data-open-modal');
        var modal = document.getElementById(id);
        if (modal) modal.classList.add('open');
    });
});

document.querySelectorAll('[data-close-modal]').forEach(function(btn) {
    btn.addEventListener('click', function() {
        var backdrop = btn.closest('.modal-backdrop');
        if (backdrop) backdrop.classList.remove('open');
    });
});

document.querySelectorAll('.modal-backdrop').forEach(function(backdrop) {
    backdrop.addEventListener('click', function(e) {
        if (e.target === backdrop) backdrop.classList.remove('open');
    });
});

document.querySelectorAll('[data-tabs-container]').forEach(function(container) {
    var buttons = container.querySelectorAll('.tab-btn');
    var panels = container.querySelectorAll('.tab-panel');

    buttons.forEach(function(btn) {
        btn.addEventListener('click', function() {
            var tabName = btn.dataset.tab;
            buttons.forEach(function(x) { x.classList.remove('active'); });
            panels.forEach(function(x) { x.classList.remove('active'); });
            btn.classList.add('active');
            var panel = container.querySelector('.tab-panel[data-tab="' + tabName + '"]');
            if (panel) panel.classList.add('active');
        });
    });
});

<?php
$show = $_GET['show'] ?? '';
if ($show === 'verify-signup') {
    echo "var m = document.getElementById('verify-signup-modal'); if (m) m.classList.add('open');";
}
if ($show === 'reset-password') {
    echo "var m2 = document.getElementById('reset-password-modal'); if (m2) m2.classList.add('open');";
}
?>

function passwordIsStrong(password) {
    if (password.length < 12) return false;
    if (!/[A-Z]/.test(password)) return false;
    if (!/[a-z]/.test(password)) return false;
    if (!/[0-9]/.test(password)) return false;
    if (!/[^a-zA-Z0-9]/.test(password)) return false;
    return true;
}

function installPasswordValidation(formSelector) {
    var form = document.querySelector(formSelector);
    if (!form) return;

    var password = form.querySelector('input[name="password"]');
    var confirmPassword = form.querySelector('input[name="password_confirm"]');

    if (!password || !confirmPassword) return;

    function validatePasswords() {
        password.setCustomValidity('');
        confirmPassword.setCustomValidity('');

        if (!passwordIsStrong(password.value)) {
            password.setCustomValidity(
                'Weak password: minimum 12 characters, with uppercase, lowercase, digit and special character.'
            );
        }

        if (password.value !== confirmPassword.value) {
            confirmPassword.setCustomValidity('Passwords do not match.');
        }
    }

    password.addEventListener('input', validatePasswords);
    confirmPassword.addEventListener('input', validatePasswords);

    form.addEventListener('submit', function(e) {
        validatePasswords();
        if (!form.checkValidity()) {
            e.preventDefault();
            form.reportValidity();
        }
    });
}

installPasswordValidation('#signup-modal form');
installPasswordValidation('#reset-password-modal form');

function getVisibleLineCount(textarea) {
    var styles = window.getComputedStyle(textarea);
    var lineHeight = parseFloat(styles.lineHeight) || 20;
    var paddingTop = parseFloat(styles.paddingTop) || 0;
    var paddingBottom = parseFloat(styles.paddingBottom) || 0;
    var innerHeight = textarea.clientHeight - paddingTop - paddingBottom;
    return Math.max(1, Math.ceil(innerHeight / lineHeight));
}

function ensureLineNumbersContent(lineBox) {
    var content = lineBox.querySelector('.line-numbers-content');
    if (!content) {
        content = document.createElement('div');
        content.className = 'line-numbers-content';
        lineBox.innerHTML = '';
        lineBox.appendChild(content);
    }
    return content;
}

function getLastNonEmptyLine(textarea) {
    var lines = textarea.value.split('\n');

    for (var i = lines.length - 1; i >= 0; i--) {
        if (lines[i].trim() !== '') {
            return i + 1;
        }
    }

    return 1;
}

function updateLineNumbers(textarea, lineBox) {
    var lastLine = getLastNonEmptyLine(textarea);
    var visibleLines = getVisibleLineCount(textarea);

    var totalLines = Math.max(lastLine, visibleLines);

    var content = ensureLineNumbersContent(lineBox);

    var nums = [];
    for (var i = 1; i <= totalLines; i++) {
        nums.push(i);
    }

    content.textContent = nums.join('\n');

    syncLineNumbers(textarea, lineBox);
}

function syncLineNumbers(textarea, lineBox) {
    var content = ensureLineNumbersContent(lineBox);
    content.style.transform = 'translateY(' + (-textarea.scrollTop) + 'px)';
}

function installLineNumbers() {
    document.querySelectorAll('[data-editor]').forEach(function(editor) {
        var textarea = editor.querySelector('textarea');
        var lineBox = editor.querySelector('.line-numbers');
        if (!textarea || !lineBox) return;

        function refresh() {
            updateLineNumbers(textarea, lineBox);
        }

        function sync() {
            syncLineNumbers(textarea, lineBox);
        }

        textarea.addEventListener('input', refresh);
        textarea.addEventListener('scroll', sync);
        textarea.addEventListener('keydown', function() {
            setTimeout(refresh, 0);
        });
        textarea.addEventListener('keyup', sync);
        textarea.addEventListener('mouseup', sync);
        textarea.addEventListener('wheel', function() {
            setTimeout(sync, 0);
        });

        if (typeof ResizeObserver !== 'undefined') {
            var ro = new ResizeObserver(function() {
                refresh();
            });
            ro.observe(textarea);
        }

        window.addEventListener('resize', refresh);

        refresh();
    });
}

installLineNumbers();

document.querySelectorAll('.symbol-toolbar').forEach(function(toolbar) {
    var textarea = toolbar.parentElement.querySelector('textarea');
    if (!textarea) return;

    toolbar.querySelectorAll('button').forEach(function(btn) {
        btn.addEventListener('click', function() {
            var symbol = btn.getAttribute('data-insert');
            var start = textarea.selectionStart;
            var end = textarea.selectionEnd;
            var text = textarea.value;

            textarea.value =
                text.substring(0, start) +
                symbol +
                text.substring(end);

            textarea.selectionStart = textarea.selectionEnd = start + symbol.length;
            textarea.focus();
            textarea.dispatchEvent(new Event('input'));
        });
    });
});
</script>
</body>
</html>