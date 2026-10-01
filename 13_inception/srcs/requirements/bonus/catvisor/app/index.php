<?php
function runCommand(string $command): string
{
    $output = shell_exec($command . ' 2>&1');
    return trim((string) $output);
}

function parseDockerRows(string $output): array
{
    $rows = [];
    foreach (array_filter(array_map('trim', explode("\n", $output))) as $line) {
        $parts = explode('|||', $line);
        if (count($parts) === 4) {
            $rows[] = [
                'name' => trim($parts[0]),
                'status' => trim($parts[1]),
                'image' => trim($parts[2]),
                'ports' => trim($parts[3]),
            ];
        }
    }

    return $rows;
}

function getDashboardData(): array
{
    $dockerOutput = runCommand("docker ps --format '{{.Names}}|||{{.Status}}|||{{.Image}}|||{{.Ports}}'");
    $dockerAccessOk = $dockerOutput !== '' && stripos($dockerOutput, 'permission denied') === false;
    $containers = $dockerAccessOk ? parseDockerRows($dockerOutput) : [];

    return [
        'dockerAccessOk' => $dockerAccessOk,
        'statusClass' => $dockerAccessOk ? 'ok' : 'bad',
        'containers' => $containers,
        'runningCount' => count($containers),
        'imageCount' => trim(runCommand("docker image ls -q | wc -l")),
        'volumeCount' => trim(runCommand("docker volume ls -q | wc -l")),
        'refreshTime' => date('Y-m-d H:i:s'),
    ];
}

if (isset($_GET['refresh']) && $_GET['refresh'] === '1') {
    header('Content-Type: application/json; charset=utf-8');
    echo json_encode(getDashboardData(), JSON_UNESCAPED_SLASHES | JSON_UNESCAPED_UNICODE);
    exit;
}

$dashboard = getDashboardData();
?>


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Catvisor | Infrastructure Monitor</title>
    <link rel="stylesheet" href="/static/css/style.css">
    <link rel="stylesheet" href="/catvisor/css/style.css">
    <link href="https://fonts.googleapis.com/css2?family=Roboto:wght@400;700&display=swap" rel="stylesheet">
</head>
<body>
    <header class="main-header">
            <a href="/static/index.html" class="logo">Home</a>
        <nav>
            <ul>
                    <li><a href="/static/developers.html">Developer</a></li>
                    <li><a href="/adminer/">Adminer</a></li>
                    <li><a href="/catvisor/">cAdvisor</a></li>
					<li><a href="/static/playground.html">Playground</a></li>
            </ul>
        </nav>
        <div></div>
    </header>

    <main class="shell">
        <div class="header">
            <div>
                <h1>Catvisor v1.0</h1>
                <p class="subtitle">Live Docker monitor for the Inception stack</p>
            </div>
            <div class="status" id="docker-status">
                <span class="dot <?php echo $dashboard['statusClass']; ?>" id="status-dot"></span>
                <span id="status-text"><?php echo $dashboard['dockerAccessOk'] ? 'DOCKER ACCESS OK' : 'DOCKER ACCESS ERROR'; ?></span>
            </div>
        </div>

        <section class="cards">
            <div class="card">
                <div class="label">Running containers</div>
                <div class="value" id="running-count"><?php echo $dashboard['runningCount']; ?></div>
                <div class="note">Live from <span class="muted">docker ps</span></div>
            </div>
            <div class="card">
                <div class="label">Images available</div>
                <div class="value" id="image-count"><?php echo $dashboard['imageCount']; ?></div>
                <div class="note">Local Docker image count</div>
            </div>
            <div class="card">
                <div class="label">Volumes mounted</div>
                <div class="value" id="volume-count"><?php echo $dashboard['volumeCount']; ?></div>
                <div class="note">Persistent data and config</div>
            </div>
            <div class="card">
                <div class="label">Last refresh</div>
                <div class="value" style="font-size: 1.1rem;" id="refresh-time"><?php echo $dashboard['refreshTime']; ?></div>
                <div class="note">Manual refresh on demand</div>
            </div>
        </section>

        <section class="section">
            <button id="refresh-btn" class="refresh-btn">🔄 Refresh Now</button>
        </section>

        <section class="section">
            <h2>Container Status</h2>
            <table>
                <thead>
                    <tr>
                        <th>Name</th>
                        <th>Status</th>
                        <th>Image</th>
                        <th>Ports</th>
                    </tr>
                </thead>
                <tbody id="container-table-body">
                <?php if ($dashboard['dockerAccessOk'] && !empty($dashboard['containers'])) : ?>
                    <?php foreach ($dashboard['containers'] as $container) : ?>
                        <tr>
                            <td><?php echo htmlspecialchars($container['name']); ?></td>
                            <td class="good"><?php echo htmlspecialchars($container['status']); ?></td>
                            <td><?php echo htmlspecialchars($container['image']); ?></td>
                            <td class="muted"><?php echo htmlspecialchars($container['ports'] ?: '-'); ?></td>
                        </tr>
                    <?php endforeach; ?>
                <?php else : ?>
                    <tr>
                        <td colspan="4" class="bad">Docker data is not available right now.</td>
                    </tr>
                <?php endif; ?>
                </tbody>
            </table>
        </section>
    </main>

    <footer style="text-align: center; padding: 20px 0; font-size: 12px; color: var(--text-subtle);">
		&copy; 2026 Inception.
	</footer>

    <script>
        const refreshUrl = new URL(window.location.href);
        refreshUrl.searchParams.set('refresh', '1');

        const refreshTime = document.getElementById('refresh-time');
        const runningCount = document.getElementById('running-count');
        const imageCount = document.getElementById('image-count');
        const volumeCount = document.getElementById('volume-count');
        const statusDot = document.getElementById('status-dot');
        const statusText = document.getElementById('status-text');
        const tableBody = document.getElementById('container-table-body');
        const refreshBtn = document.getElementById('refresh-btn');

        function escapeHtml(value) {
            return String(value)
                .replace(/&/g, '&amp;')
                .replace(/</g, '&lt;')
                .replace(/>/g, '&gt;')
                .replace(/"/g, '&quot;')
                .replace(/'/g, '&#039;');
        }

        function buildRows(containers, dockerAccessOk) {
            if (!dockerAccessOk || !containers.length) {
                return '<tr><td colspan="4" class="bad">Docker data is not available right now.</td></tr>';
            }

            return containers.map((container) => {
                const ports = container.ports || '-';

                return `
                    <tr>
                        <td>${escapeHtml(container.name)}</td>
                        <td class="good">${escapeHtml(container.status)}</td>
                        <td>${escapeHtml(container.image)}</td>
                        <td class="muted">${escapeHtml(ports)}</td>
                    </tr>
                `;
            }).join('');
        }

        async function refreshDashboard() {
            try {
                refreshBtn.disabled = true;

                const response = await fetch(refreshUrl.toString(), { cache: 'no-store' });

                if (!response.ok) {
                    refreshBtn.disabled = false;
                    return;
                }

                const data = await response.json();

                runningCount.textContent = data.runningCount;
                imageCount.textContent = data.imageCount;
                volumeCount.textContent = data.volumeCount;
                refreshTime.textContent = data.refreshTime;
                statusDot.classList.toggle('ok', data.statusClass === 'ok');
                statusDot.classList.toggle('bad', data.statusClass === 'bad');
                statusText.textContent = data.dockerAccessOk ? 'DOCKER ACCESS OK' : 'DOCKER ACCESS ERROR';
                tableBody.innerHTML = buildRows(data.containers || [], data.dockerAccessOk);

                refreshBtn.disabled = false;
            } catch (error) {
                refreshBtn.disabled = false;
                return;
            }
        }

        refreshBtn.addEventListener('click', refreshDashboard);
    </script>
</body>
</html>
