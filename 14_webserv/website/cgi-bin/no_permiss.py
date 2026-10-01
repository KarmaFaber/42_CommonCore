#!/usr/bin/env python3
# -*- coding: UTF-8 -*-

import sys
sys.stdout.reconfigure(encoding='utf-8')
print("Content-Type: text/html\r\n\r\n", end="")

print(f"""<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Permission Denied</title>
    <link rel="stylesheet" href="/css/style.css">
</head>
<body style="display: flex; justify-content: center; align-items: center; min-height: 100vh; background-color: #0f0f1d;">
    <main style="text-align: center;">
        <h1 class="main-title"><span class="gradient-text">Permission Denied</span></h1>
        <div class="comment-form" style="border-color: var(--neon-end, #FF00FF); padding: 40px; margin-top: 30px; background: #1c1c30; border: 1px solid #FF00FF; border-radius: 12px;">
            <p style="color: #e0e0e0; margin-bottom: 25px;">
                Access restricted. Please remove execution permissions from this file to proceed.
            </p>
            <a href="/error.html" class="submit-button-neon" style="text-decoration: none; display: inline-block; padding: 10px 20px; background: linear-gradient(90deg, #FF00FF, #8681ec); color: #0f0f1d; font-weight: bold; border-radius: 6px;">
                Return to Hub
            </a>
        </div>
    </main>
</body>
</html>""")