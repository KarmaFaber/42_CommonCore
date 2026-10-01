<?php
$COMMENTS_FILE_PATH = __DIR__ . '/../data/comments.txt';

function get_rendered_comments() {
	global $COMMENTS_FILE_PATH;
	if (!file_exists($COMMENTS_FILE_PATH) || filesize($COMMENTS_FILE_PATH) == 0) {
		return '<p style="color: var(--text-subtle); text-align: center; font-style: italic;">No comments yet. Be the first to post!</p>';
	}

	$lines = file($COMMENTS_FILE_PATH, FILE_IGNORE_NEW_LINES | FILE_SKIP_EMPTY_LINES);
	$cards = "";
	foreach (array_reverse($lines) as $line) {
		$parts = explode('|', $line, 5);
		if (count($parts) == 5) {
			list($id, $date, $author, $subject, $body) = $parts;
			$cards .= "<div class='comment-card' style='background-color: var(--bg-medium, #1c1c30); padding: 25px; border-radius: 8px; margin-bottom: 20px; border: 1px solid rgba(0, 255, 255, 0.1);'>
						<div class='comment-header' style='display: flex; justify-content: space-between; margin-bottom: 15px; border-bottom: 1px solid rgba(255, 255, 255, 0.05); padding-bottom: 8px;'>
							<span class='comment-author' style='color: var(--neon-start, #00FFFF); font-weight: bold;'>@$author</span>
							<span class='comment-date' style='color: var(--text-subtle, #a0a0a0); font-size: 12px;'>$date</span>
						</div>
						<div class='comment-body'>
							<h4 style='color: #fff; margin-bottom: 10px; font-size: 16px;'>$subject</h4>
							<p style='color: var(--text-light, #e0e0e0); line-height: 1.5; font-size: 14px;'>$body</p>
						</div>
					   </div>";
		}
	}
	return $cards;
}
?>
<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<title>Board Logs - Webserv</title>
	<link rel="icon" href="data:,">
	<link href="https://fonts.googleapis.com/css2?family=Roboto:wght@300;400;700&display=swap" rel="stylesheet">
	<link rel="stylesheet" href="/css/style.css">
</head>
<body>
	<header class="main-header">
		<a href="/index.html" class="logo">Home</a>
		<nav>
			<ul style="display: flex; align-items: center;">
				<li><a href="/developers.html">Developers</a></li>
				<li><a href="/comments.html">Comments</a></li>
				<li><a href="/files.html">Files</a></li>
				<li><a href="/error.html">Error_checks</a></li>
				
				<li style="margin-left: 200px; border-left: 1px solid rgba(255,255,255,0.2); height: 15px;"></li>
				<li style="margin-left: 5px;"></li>
				
				<li><a href="/login.html">Login</a></li>
				<li><a href="/cgi-bin/profile.php" data-cgi-php="/cgi-bin/profile.php" data-cgi-py="/cgi-bin/profile.py">Profile</a></li>
				<li><a href="/cgi-bin/logout.php" data-cgi-php="/cgi-bin/logout.php" data-cgi-py="/cgi-bin/logout.py">Logout</a></li>
			</ul>
		</nav>
		<div></div>
		<select id="cgi-selector" onchange="updateCGI()">
			<option value=".php">PHP</option>
			<option value=".py">Python</option>
		</select>
	</header>

	<main>
		<section class="intro-section">
			<h1 class="main-title">
				<span class="gradient-text">Live Feed</span>
			</h1>
		</section>

		<section class="form-container" style="margin-bottom: 60px;">
			<div class="comment-form" style="padding: 30px; border-color: var(--neon-start, #00FFFF);">
				<div style="display: flex; justify-content: space-between; align-items: center; margin-bottom: 30px;">
					<h3 style="margin: 0;">Messages fetched from database</h3>
					<a href="/comments.html" class="submit-button-neon" style="text-decoration: none; font-size: 12px; padding: 6px 15px; width: auto; margin: 0;">&larr; Back to Post</a>
				</div>
				
				<div class="comments-wrapper">
					<?php echo get_rendered_comments(); ?>
				</div>
			</div>
		</section>
	</main>
	<script src="/js/cgi-switcher.js"></script>
	<footer class="main-footer">
		<div class="footer-container">
			<p class="footer-copy">&copy; 2026 Webserv.</p>
		</div>
	</footer>
</body>
</html>
