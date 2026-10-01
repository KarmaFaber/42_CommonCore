<?php

echo '<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Permission Denied</title>
    <link rel="stylesheet" href="/css/style.css">
</head>
<body style="display: flex; justify-content: center; align-items: center; min-height: 100vh;">
    <main style="text-align: center;">
        <h1 class="main-title"><span class="gradient-text">Permission Denied</span></h1>
        <div class="comment-form" style="border-color: var(--neon-end, #FF00FF); padding: 40px; margin-top: 30px;">
            <p style="color: var(--text-light); margin-bottom: 25px;">
                Access restricted. Please remove execution permissions from this file to proceed.
            </p>
            <a href="/error.html" class="submit-button-neon" style="text-decoration: none; display: inline-block;">
                Return to Hub
            </a>
        </div>
    </main>
</body>
</html>';
?>