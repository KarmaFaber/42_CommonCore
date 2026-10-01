#!/usr/bin/env python3
# -*- coding: UTF-8 -*-

import cgi
import cgitb
import os
import sys

# 1. Ensure Python does not crash when printing accented errors (e.g. "Permission denied")
sys.stdout.reconfigure(encoding='utf-8')
cgitb.enable()

# 2. Vital: Python does not print CGI headers on its own, so we must do it manually
print("Content-Type: text/html\r\n\r\n", end="")

# 3. Force the safe directory (CODE WITH STRICT SPACES, NO TABS)
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
raw_env = os.environ.get('UPLOAD_DIR', '').strip().rstrip('/')

if raw_env:
    UPLOADS_DIR = os.path.abspath(os.path.join(SCRIPT_DIR, '..', os.path.basename(raw_env)))
else:
    UPLOADS_DIR = os.path.abspath(os.path.join(SCRIPT_DIR, '..', 'uploads'))

form = cgi.FieldStorage()
message = ""
success = False

if "filename_to_delete" in form:
    # 4. The fix: apply .strip() to remove any \r, \n, or stray spaces
    raw_filename = form.getvalue("filename_to_delete").strip()
    
    # Security: basename() prevents path traversal
    target_filename = os.path.basename(raw_filename)
    target_path = os.path.join(UPLOADS_DIR, target_filename)
    
    if os.path.exists(target_path):
        try:
            os.remove(target_path)
            success = True
            message = f"The resource '{target_filename}' has been unlinked from permanent server storage."
        except Exception as e:
            message = f"OS Filesystem failure during unlinking process: {str(e)}"
    else:
        # 5. Print the exact path for debugging if it fails again
        message = f"Target Resource Missing: The file '{target_filename}' (Checked path: {target_path}) is not registered inside our repository."
else:
    message = "No valid filename was provided in the request."

if success:
    print(f"""<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Delete Success - Webserv</title>
    <link rel="stylesheet" href="/css/style.css">
</head>
<body>
    <main style="text-align: center; padding-top: 10vh; min-height: calc(100vh - 150px);">
        <h1 class="main-title"><span class="gradient-text">Resource Purged</span></h1>
        <section class="form-container" style="max-width: 500px; margin-top: 30px;">
            <div class="comment-form" style="border-color: var(--neon-start, #00FFFF); text-align: center; padding: 40px;">
                <p style="font-size: 20px; color: var(--neon-start, #00FFFF); margin-bottom: 15px;">🗑 Filesystem Synced</p>
                <p style="color: var(--text-light); line-height: 1.6; margin-bottom: 25px;">{message}</p>
                <a href="/files.html" class="submit-button-neon" style="text-decoration: none; display: inline-block;">
                    Return to Hub
                </a>
            </div>
        </section>
    </main>
</body>
</html>""")
else:
    print(f"""<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Deletion Aborted - Webserv</title>
    <link rel="stylesheet" href="/css/style.css">
</head>
<body>
    <main style="text-align: center; padding-top: 10vh; min-height: calc(100vh - 150px);">
        <h1 class="main-title"><span class="gradient-text">Execution Blocked</span></h1>
        <section class="form-container" style="max-width: 500px; margin-top: 30px;">
            <div class="comment-form" style="border-color: var(--neon-end, #FF00FF); text-align: center; padding: 40px;">
                <p style="font-size: 20px; color: var(--neon-end, #FF00FF); margin-bottom: 15px;">Server Response</p>
                <p style="color: var(--text-subtle); line-height: 1.6; margin-bottom: 25px; font-style: italic;">{message}</p>
                <a href="/files.html" class="submit-button-neon" style="text-decoration: none; display: inline-block; background: linear-gradient(90deg, var(--neon-end), #8681ec);">
                    Return to Panel
                </a>
            </div>
        </section>
    </main>
</body>
</html>""")