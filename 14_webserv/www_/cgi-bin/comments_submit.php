<?php
$COMMENTS_FILE_PATH = __DIR__ . '/../data/comments.txt';

if (!is_dir(dirname($COMMENTS_FILE_PATH))) {
	mkdir(dirname($COMMENTS_FILE_PATH), 0777, true);
}

$username = $_POST['username'] ?? '';
$subject = $_POST['subject'] ?? '';
$comment = $_POST['comment'] ?? '';

$success = false;
$error_msg = "";

if (!empty($username) && !empty($subject) && !empty($comment)) {
	try {
		$comment_id = time() . mt_rand(100, 999);
		$timestamp = date("Y-m-d");
		$clean_comment = str_replace(["\n", "\r"], ' ', $comment);
		
		$line = "$comment_id|$timestamp|$username|$subject|$clean_comment\n";
		file_put_contents($COMMENTS_FILE_PATH, $line, FILE_APPEND);
		$success = true;
	} catch (Exception $e) {
		$error_msg = "Storage Error: " . $e->getMessage();
	}
} else {
	$error_msg = "Validation Error: All fields are required.";
}
?>
<!DOCTYPE html>
<html lang="en">
<head><title><?php echo $success ? "Success" : "Error"; ?> - Webserv</title>
<link rel="stylesheet" href="/css/style.css"></head>
<body>
	<main style="text-align: center; padding-top: 10vh;">
		<h1 class="main-title"><span class="gradient-text"><?php echo $success ? "Message Posted" : "Submission Failed"; ?></span></h1>
		<section class="form-container" style="max-width: 500px; margin-top: 30px;">
			<div class="comment-form" style="border-color: <?php echo $success ? 'var(--neon-start)' : 'var(--neon-end)'; ?>; padding: 40px;">
				<p style="font-size: 20px; color: <?php echo $success ? 'var(--neon-start)' : 'var(--neon-end)'; ?>;">
					<?php echo $success ? "Comment Broadcasted" : "Transaction Aborted"; ?>
				</p>
				<p style="color: var(--text-light);"><?php echo $success ? "Your entry is saved." : $error_msg; ?></p>
				<a href="/cgi-bin/comments_view.php" class="submit-button-neon">View Messagesboard</a>
			</div>
		</section>
	</main>
</body>
</html>
