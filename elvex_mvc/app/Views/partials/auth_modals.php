<?php if (!is_logged_in()): ?>
<div class="modal-backdrop" id="signup-modal">
    <div class="modal">
        <div class="modal-header">Create Account</div>
        <form method="post" action="<?= e(url_path('signup/request')) ?>">
            <div class="modal-body">
                <input type="hidden" name="_csrf" value="<?= e(csrf_token()) ?>">
                <div class="row">
                    <label>Account Name</label>
                    <input type="text" name="display_name" required>
                </div>
                <div class="row">
                    <label>Email</label>
                    <input type="email" name="email" required>
                </div>
                <div class="row">
                    <label>Password</label>
                    <input type="password" name="password" required>
                </div>
                <div class="row">
                    <label>Confirm Password</label>
                    <input type="password" name="password_confirm" required>
                </div>
                <p class="hint">The password must contain at least 12 characters, with uppercase, lowercase, number and special character.</p>
                <p class="hint">A code will be sent by email to finalize the account creation.</p>
            </div>
            <div class="modal-footer">
                <button type="button" class="btn secondary" data-close-modal>Cancel</button>
                <button type="submit" class="btn primary">Send Code</button>
            </div>
        </form>
    </div>
</div>

<div class="modal-backdrop" id="verify-signup-modal">
    <div class="modal">
        <div class="modal-header">Validate Account</div>
        <form method="post" action="<?= e(url_path('signup/verify')) ?>">
            <div class="modal-body">
                <input type="hidden" name="_csrf" value="<?= e(csrf_token()) ?>">
                <div class="row">
                    <label>Email</label>
                    <input type="email" name="email" value="<?= e($_GET['email'] ?? '') ?>" required>
                </div>
                <div class="row">
                    <label>Code received by email</label>
                    <input type="text" name="code" required>
                </div>
            </div>
            <div class="modal-footer">
                <button type="button" class="btn secondary" data-close-modal>Cancel</button>
                <button type="submit" class="btn primary">Validate</button>
            </div>
        </form>
    </div>
</div>

<div class="modal-backdrop" id="signin-modal">
    <div class="modal">
        <div class="modal-header">Sign In</div>
        <form method="post" action="<?= e(url_path('signin')) ?>">
            <div class="modal-body">
                <input type="hidden" name="_csrf" value="<?= e(csrf_token()) ?>">
                <div class="row">
                    <label>Email</label>
                    <input type="email" name="email" required>
                </div>
                <div class="row">
                    <label>Password</label>
                    <input type="password" name="password" required>
                </div>
                <p class="hint"><a href="#" data-open-modal="forgot-password-modal" data-close-parent-modal="signin-modal">Mot de passe oublié ?</a></p>
            </div>
            <div class="modal-footer">
                <button type="button" class="btn secondary" data-close-modal>Cancel</button>
                <button type="submit" class="btn primary">Sign In</button>
            </div>
        </form>
    </div>
</div>

<div class="modal-backdrop" id="forgot-password-modal">
    <div class="modal">
        <div class="modal-header">Forgot Password</div>
        <form method="post" action="<?= e(url_path('password/recovery/request')) ?>">
            <div class="modal-body">
                <input type="hidden" name="_csrf" value="<?= e(csrf_token()) ?>">
                <div class="row">
                    <label>Email</label>
                    <input type="email" name="email" value="<?= e($_GET['email'] ?? '') ?>" required>
                </div>
                <p class="hint">A code will be sent by email to define a new password.</p>
            </div>
            <div class="modal-footer">
                <button type="button" class="btn secondary" data-close-modal>Cancel</button>
                <button type="submit" class="btn primary">Send Code</button>
            </div>
        </form>
    </div>
</div>

<div class="modal-backdrop" id="reset-password-modal">
    <div class="modal">
        <div class="modal-header">Reset Password</div>
        <form method="post" action="<?= e(url_path('password/recovery/confirm')) ?>">
            <div class="modal-body">
                <input type="hidden" name="_csrf" value="<?= e(csrf_token()) ?>">
                <div class="row">
                    <label>Email</label>
                    <input type="email" name="email" value="<?= e($_GET['email'] ?? '') ?>" required>
                </div>
                <div class="row">
                    <label>Code received by email</label>
                    <input type="text" name="code" required>
                </div>
                <div class="row">
                    <label>New password</label>
                    <input type="password" name="password" required>
                </div>
                <div class="row">
                    <label>Confirm new password</label>
                    <input type="password" name="password_confirm" required>
                </div>
                <p class="hint">The password must contain at least 12 characters, with uppercase, lowercase, digit and special character.</p>
            </div>
            <div class="modal-footer">
                <button type="button" class="btn secondary" data-close-modal>Cancel</button>
                <button type="submit" class="btn primary">Reset Password</button>
            </div>
        </form>
    </div>
</div>
<?php endif; ?>
