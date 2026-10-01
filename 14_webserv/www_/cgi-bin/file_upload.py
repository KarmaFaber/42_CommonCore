#!/usr/bin/env python3
# -*- coding: UTF-8 -*-

import cgi
import cgitb
import os
import sys

# 1. Security and encoding setup
sys.stdout.reconfigure(encoding='utf-8')
cgitb.enable()

# 2. Mandatory headers for the Web Server (CGI)
print("Content-Type: text/html\r\n\r\n", end="")

# 3. Force a safe path
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
raw_env = os.environ.get('UPLOAD_DIR', '').strip().rstrip('/')

if raw_env:
    UPLOADS_DIR = os.path.abspath(os.path.join(SCRIPT_DIR, '..', os.path.basename(raw_env)))
else:
    UPLOADS_DIR = os.path.abspath(os.path.join(SCRIPT_DIR, '..', 'uploads'))

form = cgi.FieldStorage()
message = ""
success = False

# 4. Upload logic
if "file_to_upload" in form:
    fileitem = form["file_to_upload"]
    
    if fileitem.filename:
        filename = os.path.basename(fileitem.filename)
        try:
            os.makedirs(UPLOADS_DIR, exist_ok=True)
            target_path = os.path.join(UPLOADS_DIR, filename)
            
            with open(target_path, 'wb') as f:
                while True:
                    chunk = fileitem.file.read(1024 * 64)
                    if not chunk: break
                    f.write(chunk)
            
            success = True
            message = f"File '{filename}' successfully buffered and written to permanent storage."
        except Exception as e:
            message = f"File system write failure: {str(e)}"
    else:
        message = "No clear payload detected."
else:
    message = "Invalid multipart boundary request configuration."

# 5. Consistent rendering (same layout as delete)
page_title = "Upload Success" if success else "Upload Aborted"
main_heading = "Upload Complete" if success else "Pipeline Error"
icon_text = "Disk Stream Confirmed" if success else "Pipeline Error"
border_color = "var(--neon-start)" if success else "var(--neon-end)"
text_color = "var(--text-light)" if success else "var(--text-subtle)"

print(f"""<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>{page_title} - Webserv</title>
    <link rel="stylesheet" href="/css/style.css">
</head>
<body>
    <header class="main-header">
        <a href="/index.html" class="logo">Home</a>
        <nav><ul><li><a href="/files.html">Files</a></li></ul></nav>
        <div style="width: 120px;"></div>
    </header>

    <main style="min-height: calc(100vh - 150px); display: flex; flex-direction: column; align-items: center; justify-content: center;">
        <h1 class="main-title"><span class="gradient-text">{main_heading}</span></h1>
        <section class="form-container" style="width: 100%; max-width: 500px; margin-top: 20px;">
            <div class="comment-form" style="border-color: {border_color}; text-align: center; padding: 40px;">
                <p style="font-size: 20px; color: {border_color}; font-weight: bold; margin: 0;">{icon_text}</p>
                <p style="color: {text_color}; line-height: 1.6; margin: 15px 0;">{message}</p>
                <a href="/files.html" class="submit-button-neon" style="text-decoration: none; display: block; text-align: center;">Return to Hub</a>
            </div>
        </section>
    </main>
    <footer class="main-footer"><div class="footer-container"><p class="footer-copy">&copy; 2026 Webserv.</p></div></footer>
</body>
</html>""")