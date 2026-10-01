<?php
// 1. Force the safe uploads directory
$raw_env = getenv('UPLOAD_DIR');
if ($raw_env && $raw_env !== "") {
    $target_folder = basename($raw_env);
    $upload_dir = __DIR__ . '/../' . $target_folder;
} else {
    $upload_dir = __DIR__ . '/../uploads';
}

$message = "";
$success = false;

// 2. Check a regular text field (POST)
if ($_SERVER['REQUEST_METHOD'] === 'POST' && !empty($_POST['filename_to_delete'])) {
    
    // 3. Security: basename() cuts off any "../" attempt and leaves only the final name
    $target_filename = basename($_POST['filename_to_delete']);
    $target_path = $upload_dir . '/' . $target_filename;
    
    if (file_exists($target_path)) {
        if (unlink($target_path)) {
            $success = true;
            $message = "The resource '$target_filename' has been safely unlinked from storage.";
        } else {
            $message = "OS Filesystem failure during unlinking process.";
        }
    } else {
        $message = "Target Resource Missing: '$target_filename' not found.";
    }
} else {
    $message = "No valid filename provided.";
}
?>
<!DOCTYPE html>
<html lang="en">
<head><title>Delete <?php echo $success ? "Success" : "Abort"; ?></title><link rel="stylesheet" href="/css/style.css"></head>
<body>
	<main style="text-align: center; padding-top: 10vh;">
		<h1 class="main-title"><span class="gradient-text"><?php echo $success ? "Resource Purged" : "Execution Blocked"; ?></span></h1>
		<div class="comment-form" style="border-color: <?php echo $success ? 'var(--neon-start)' : 'var(--neon-end)'; ?>;">
			<p><?php echo $message; ?></p>
			<a href="/files.html" class="submit-button-neon">Return to Hub</a>
		</div>
	</main>
</body>
</html>
