<?php

$session = getenv('BONUS_SESSION');

if ($session === NULL || $session === false || $session === '') {
	header("Location: /index.html", true, 302);
    exit;
}

header("Content-Type: text/html; charset=utf-8");
header("Bonus-Delete-Session: " . $session);
http_response_code(200);
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
		<h1 class="main-title"><span class="gradient-text">Logged out succesfully</span></h1>
		<section class="form-container" style="max-width: 500px; margin-top: 30px;">
			<div class="comment-form" style="border-color: #00FFFF; text-align: center;">
				<p style="font-size: 18px; color: #00FFFF;">Logout Successful</p>
				<p style="color: var(--text-light); margin: 15px 0;">Your session has been deleted.</p>
				<code style="background: var(--bg-dark); padding: 10px; display: block; border-radius: 4px; color: var(--neon-end); font-size: 13px;">Cookie deleted: <?php echo htmlspecialchars($session); ?></code>
				<a href="/index.html" class="submit-button-neon" style="text-decoration: none; display: inline-block; margin-top: 20px; text-align: center;">Go to Home</a>
			</div>
		</section>
	</main>
</body>
</html>
