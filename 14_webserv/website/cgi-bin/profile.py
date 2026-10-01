#!/usr/bin/env python3
# -*- coding: UTF-8 -*-

import os
import sys

session = os.getenv("BONUS_SESSION")

# 1. Check whether there is an active session. If not, redirect to the login page.
if not session:
    print("Status: 302 Found")
    print("Location: /login.html")
    print()
    exit(0)

username = os.getenv("BONUS_USERNAME", "Unknown")
email = os.getenv("BONUS_EMAIL", "Unknown")

# 2. Print headers for a successful response
sys.stdout.reconfigure(encoding='utf-8')

print("Content-Type: text/html; charset=utf-8")
print() # Línea en blanco obligatoria

# 3. Renderizar el HTML con el estilo de Webserv
print(f"""<!DOCTYPE html>
<html lang="en" lang="es">
<head>
    <meta charset="UTF-8">
    <title>Profile - Webserv</title>
    <link rel="stylesheet" href="/css/style.css">
</head>
<body>
    <main style="text-align: center; padding-top: 10vh; display: flex; flex-direction: column; align-items: center;">
        <h1 class="main-title"><span class="gradient-text">User Profile</span></h1>
        
        <section class="form-container" style="max-width: 600px; margin-top: 30px; width: 100%%;">
            <div class="comment-form" style="border-color: var(--neon-start); text-align: left;">
                <h2 style="color: var(--neon-start); margin-bottom: 20px; text-align: center;">Welcome, %s!</h2>
                
                <div style="background: var(--bg-dark); padding: 15px; border-radius: 6px; border: 1px solid rgba(0, 255, 255, 0.3); margin-bottom: 15px;">
                    <p style="margin-bottom: 10px; font-size: 16px;">
                        <strong style="color: var(--neon-end);">Email:</strong> 
                        <span style="color: var(--text-light);">%s</span>
                    </p>
                    <p style="font-size: 16px;">
                        <strong style="color: var(--neon-end);">Session Token:</strong> 
                        <span style="color: var(--text-light); font-family: monospace; word-break: break-all;">%s</span>
                    </p>
                </div>
                <div style="display: flex; justify-content: center; gap: 15px; margin-top: 25px;">
                    <a href="/index.html" class="submit-button-neon" style="text-decoration: none; text-align: center;">Go to Home</a>
                    <a href="/cgi-bin/logout.py" class="submit-button-neon" style="text-decoration: none; text-align: center; background: transparent; border: 1px solid var(--neon-end); color: var(--neon-end); box-shadow: none;">Logout</a>
                </div>
            </div>
        </section>
    </main>
</body>

</html>

""" % (username, email, session))