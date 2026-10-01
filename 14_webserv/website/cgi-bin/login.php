#!/usr/bin/env php
<?php
// -*- coding: UTF-8 -*-

ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

$session = getenv('BONUS_SESSION') ?: '';
$session = trim($session);

$username = isset($_POST['username']) ? $_POST['username'] : null;
$email = isset($_POST['email']) ? $_POST['email'] : null;

if (strlen($session) == 0) {
	// Set cookie
	header("Status: 200 Ok");
	header("Bonus-Create-Session: yes");
	if ($username) header("Bonus-Username: " . $username);
    if ($email) header("Bonus-Email: " . $email);
	#setcookie("session_id", $session_id, time() + 86400, "/", "", false, true);

	?>
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <title>Dashboard - Webserv</title>
        <link rel="stylesheet" href="/css/style.css">
    </head>
    <body>
        <main style="text-align: center; padding-top: 10vh;">
            <h1 class="main-title"><span class="gradient-text">Welcome back!</span></h1>
            <section class="form-container" style="max-width: 500px; margin-top: 30px;">
                <div class="comment-form" style="border-color: #00FFFF; text-align: center;">
                    <p style="font-size: 18px; color: #00FFFF;">Login Successful</p>
                    <p style="color: var(--text-light); margin: 15px 0;">Your session has been initialized via HTTP Cookies.</p>
                    <code style="background: var(--bg-dark); padding: 10px; display: block; border-radius: 4px; color: var(--neon-end); font-size: 13px;"></code>
                    <a href="/index.html" class="submit-button-neon" style="text-decoration: none; display: inline-block; margin-top: 20px; text-align: center;">Go to Home</a>
                </div>
            </section>
        </main>
    </body>
    </html>
    <?php
} else { //session already set, redirect to profile page
	header("Status: 302 Found");
    header("Location: /cgi-bin/profile.php");
}