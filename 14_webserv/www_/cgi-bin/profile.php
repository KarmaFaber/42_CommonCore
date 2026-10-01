#!/usr/bin/env php
<?php
// -*- coding: UTF-8 -*-

$session = getenv("BONUS_SESSION");

// 1. Check whether there is an active session. If not, redirect to the login page.
if ($session === NULL || $session === false || $session === '') {
    header("Status: 302 Found");
    header("Location: /login.html");
    exit(0);
}

$username = getenv("BONUS_USERNAME") ?: "Unknown";
$email = getenv("BONUS_EMAIL") ?: "Unknown";

// 2. Print headers for a successful response
header("Content-Type: text/html; charset=utf-8");

// 3. Renderizar el HTML con el estilo de Webserv
echo <<<HTML
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Profile - Webserv</title>
    <link rel="stylesheet" href="/css/style.css">
</head>
<body>
    <main style="text-align: center; padding-top: 10vh; display: flex; flex-direction: column; align-items: center;">
        <h1 class="main-title"><span class="gradient-text">User Profile</span></h1>
        
        <section class="form-container" style="max-width: 600px; margin-top: 30px; width: 100%;">
            <div class="comment-form" style="border-color: var(--neon-start); text-align: left;">
                <h2 style="color: var(--neon-start); margin-bottom: 20px; text-align: center;">Welcome, $username!</h2>
                
                <div style="background: var(--bg-dark); padding: 15px; border-radius: 6px; border: 1px solid rgba(0, 255, 255, 0.3); margin-bottom: 15px;">
                    <p style="margin-bottom: 10px; font-size: 16px;">
                        <strong style="color: var(--neon-end);">Email:</strong> 
                        <span style="color: var(--text-light);">$email</span>
                    </p>
                    <p style="font-size: 16px;">
                        <strong style="color: var(--neon-end);">Session Token:</strong> 
                        <span style="color: var(--text-light); font-family: monospace; word-break: break-all;">$session</span>
                    </p>
                </div>
                <div style="display: flex; justify-content: center; gap: 15px; margin-top: 25px;">
                    <a href="/index.html" class="submit-button-neon" style="text-decoration: none; text-align: center;">Go to Home</a>
                    <a href="/cgi-bin/logout.php" class="submit-button-neon" style="text-decoration: none; text-align: center; background: transparent; border: 1px solid var(--neon-end); color: var(--neon-end); box-shadow: none;">Logout</a>
                </div>
            </div>
        </section>
    </main>
</body>
</html>
HTML;
?>