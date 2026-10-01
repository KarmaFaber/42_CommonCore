<?php
// 1. Force the safe uploads directory
$raw_env = getenv('UPLOAD_DIR');
if ($raw_env && $raw_env !== "") {
    $target_folder = basename($raw_env);
    $upload_dir = __DIR__ . '/../' . $target_folder;
} else {
    $upload_dir = __DIR__ . '/../uploads';
}

// Try to create the directory if it does not exist and capture permission errors
$dir_error = "";
if (!is_dir($upload_dir)) {
    if (!@mkdir($upload_dir, 0755, true)) {
        $dir_error = "Permission denied: Cannot create upload directory.";
    }
} elseif (!is_writable($upload_dir)) {
    $dir_error = "Permission denied: Upload directory is not writable.";
}

$message = "";
$success = false;

// 2. Check the upload
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    if (!empty($dir_error)) {
        $message = $dir_error;
    } elseif (isset($_FILES['file_to_upload'])) {
        $fileitem = $_FILES['file_to_upload'];
        
        if ($fileitem['error'] !== UPLOAD_ERR_OK) {
            $message = "Upload failed with error code: " . $fileitem['error'];
        } elseif (!empty($fileitem['name'])) {
            $filename = basename($fileitem['name']);
            $target_path = $upload_dir . '/' . $filename;
            
            if (move_uploaded_file($fileitem['tmp_name'], $target_path)) {
                $success = true;
                $message = "File '$filename' successfully buffered and written to permanent storage.";
            } else {
                $message = "OS Filesystem write failure: Cannot move uploaded file to destination.";
            }
        } else {
            $message = "No clear payload detected in the form transmission.";
        }
    } else {
        $message = "Invalid request configuration: 'file_to_upload' missing in POST data.";
    }
} else {
    $message = "Invalid request method.";
}
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Upload <?php echo $success ? "Success" : "Error"; ?> - Webserv</title>
    <link rel="stylesheet" href="/css/style.css">
</head>
<body>
    <main style="text-align: center; padding-top: 10vh; min-height: calc(100vh - 150px);">
        <h1 class="main-title"><span class="gradient-text"><?php echo $success ? "Upload Complete" : "Pipeline Error"; ?></span></h1>
        <section class="form-container" style="max-width: 500px; margin-top: 30px;">
            <div class="comment-form" style="border-color: <?php echo $success ? 'var(--neon-start)' : 'var(--neon-end)'; ?>; padding: 40px;">
                <p style="font-size: 20px; color: <?php echo $success ? 'var(--neon-start)' : 'var(--neon-end)'; ?>; margin-bottom: 15px;">
                    <?php echo $success ? "Disk Stream Confirmed" : "Pipeline Error"; ?>
                </p>
                <p style="color: var(--text-light); line-height: 1.6; margin-bottom: 25px;"><?php echo $message; ?></p>
                <a href="/files.html" class="submit-button-neon" style="text-decoration: none; display: inline-block;">Return to File Hub</a>
            </div>
        </section>
    </main>
</body>
</html>