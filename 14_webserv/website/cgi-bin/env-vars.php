<?php
// Set content type for proper HTML rendering
header('Content-Type: text/html; charset=UTF-8');

// Get all environment variables as an associative array
$envVars = getenv();

// Validate that we actually got an array
if (!is_array($envVars)) {
    echo "<p>No environment variables found.</p>";
    exit;
}

// Sort variables alphabetically for easier reading
ksort($envVars);

// Output as an HTML table
echo "<!DOCTYPE html><html><head><title>Environment Variables</title>";
echo "<style>
        body { font-family: Arial, sans-serif; margin: 20px; }
        table { border-collapse: collapse; width: 100%; }
        th, td { border: 1px solid #ccc; padding: 8px; text-align: left; }
        th { background-color: #f4f4f4; }
      </style></head><body>";

echo "<h1>Environment Variables</h1>";
echo "<table>";
echo "<tr><th>Variable</th><th>Value</th></tr>";

foreach ($envVars as $key => $value) {
    // Escape output to prevent HTML injection
    $safeKey = htmlspecialchars($key, ENT_QUOTES, 'UTF-8');
    $safeValue = htmlspecialchars($value, ENT_QUOTES, 'UTF-8');
    echo "<tr><td>{$safeKey}</td><td>{$safeValue}</td></tr>";
}

echo "</table></body></html>";
