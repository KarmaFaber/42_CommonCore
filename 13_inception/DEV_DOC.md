
# Developer Documentation - Inception

This documentation provides the necessary steps to set up the environment, build the infrastructure, and manage the services for the Inception project.

## 1. System Environment

* **Operating Systems:**
    - **Development/Server:** Debian 13 (Trixie/Testing).
    - **Laptop/Testing:** Ubuntu 22.04.5 LTS.
* **Architecture:** amd64.
* **GUI / Browser Environment**:
    - A lightweight XFCE4 desktop environment with Firefox ESR has been installed on the server VM.

    - Purpose: This enables internal DNS resolution testing and web accessibility validation directly from the VM host, bypassing system-wide network restrictions and DNS filtering present in the evaluation cluster.

* **Kernel Note:** This setup follows modern Linux security standards (GPG keyring management) to ensure compatibility with recent kernel updates regarding process isolation and repository integrity.

## 2. Environment Setup (From Scratch)

### A. Initial Dependencies

Install the essential tools to manage repositories and build the project:

```bash
sudo apt update && sudo apt install -y \
    curl gnupg ca-certificates lsb-release git make sudo
```

### B. Docker Engine Installation

To ensure compatibility and performance, use the official Docker repository.

1. **Add GPG Key:**

```bash
sudo install -m 0755 -d /etc/apt/keyrings
curl -fsSL https://download.docker.com/linux/debian/gpg | sudo gpg --dearmor -o /etc/apt/keyrings/docker.gpg
sudo chmod a+r /etc/apt/keyrings/docker.gpg
```

2. **Setup Repository:**
```bash
echo "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.gpg] \
https://download.docker.com/linux/debian $(lsb_release -cs) stable" | \
sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
```

3. **Install Engine:**
```bash
sudo apt update && sudo apt install -y \
docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
```

### C. Sudo Privileges
To allow the Makefile and Docker scripts to run without password interruptions, ensure your user is in the sudoers file:
1. Run `sudo visudo`.
2. Add the following line at the end (replace `your_login` with your actual login):
   `your_login ALL=(ALL) NOPASSWD:ALL`

### D. Instalar FTP server
sudo apt update
sudo apt install lftp


## 3. Project Configuration

### Local DNS
Map the project domain in your host's `/etc/hosts` file (replace with your 42 login if necessary)

```bash
127.0.0.1  login.42.fr
```

### Environment Variables
Create a `.env` file in the `srcs/` directory using `.env.example` as a template.
**Note:** Never commit the `.env` file to the repository.

## 4. Build and Launch
The infrastructure is orchestrated via a **Makefile** located at the root of the project:

| Command | Action |
| :--- | :--- |
| `make` | Orchestrates the full build and starts containers in detached mode. |
| `make bonus` | Starts the mandatory part plus additional services. |
| `make status` | Quick check of running containers and their health. |
| `make logs` | Real-time stream of all service logs. |
| `make down` | Gracefully stops and removes containers and networks. |
| `make fclean` | Hard Reset: Stops services and deletes all physical data in `~/data`. |

## 5. Data Storage and Persistence
Data is persisted using **Docker Volumes** mapped to the host's filesystem using the `local` driver and `bind` options to ensure no data loss during container restarts:

**Host paths:**
* **Database Data:** `/home/login/data/mariadb_data` (Mapped to `/var/lib/mysql`)
* **WordPress Files:** `/home/login/data/wordpress_data` (Mapped to `/var/www/html`)

> [!IMPORTANT]
> The `make` setup rule automatically creates these directories and sets the necessary permissions (`777` for the evaluation environment) before launching the containers.


---

> [!NOTE]
> If you need to sync your local repository changes to the VM, use scp through the established SSH tunnel (port 4343):

Execute this from your 42 PC terminal (inception repo):
```bash
#copy all repo files
scp -P 4343 -r * mzolotar@127.0.0.1:/home/mzolotar/inception_defver

#copy .env file 
#scp -P 4343 /home/mzolotar/Videos/inception_env/.env mzolotar@127.0.0.1:/home/mzolotar/inception_defver/srcs/
```

## 6. Management and Debugging

### Network Infrastructure & Service Connectivity
The infrastructure uses a dedicated bridge network (`inception_net`) to ensure isolation.

* **Internal DNS:** Containers communicate using their **service names** (e.g., `mariadb`, `wordpress`) instead of volatile IP addresses.
* **Network Inspection:** To identify that containers are correctly attached to the private network, use:
```bash
sudo docker network ls
sudo docker network inspect inception_inception_net
```

### General Management
* **Execute commands in container:** `sudo docker exec -it <container_name> <command>`
* **Network Inspection:** `sudo docker network ls` or `sudo docker network inspect inception_net`
* **Volume Inspection:** `sudo docker volume ls` or `docker volume inspect <volume_name>`
```bash
sudo docker volume ls
sudo docker volume inspect inception_wordpress_data
sudo docker volume inspect inception_mariadb_data
```

### Validation of HTTPS Infrastructure Connectivity
```bash
curl -Ik https://mzolotar.42.fr/
```

### Data Verification
- Check local volume persistence:
```bash
ls -la ~/data/wordpress_data
ls -la ~/data/mariadb_data
```
- Query Database (Users & Comments):
```bash
sudo docker exec -it mariadb mariadb -u <SQL_USER> -p<SQL_PASSWORD> inception_db -e "SELECT user_login, user_email, user_status FROM wp_users;"
sudo docker exec -it mariadb mariadb -u <SQL_USER> -p<SQL_PASSWORD> inception_db -e "SELECT comment_author, comment_content, comment_approved FROM wp_comments;"
```
- Manual Database Audit:
```bash
# Connect as mzolotar user
sudo docker exec -it mariadb mariadb -u <SQL_USER> -p<SQL_PASSWORD> inception_db

# Useful SQL Commands once inside:
SHOW TABLES;
USE inception_db;
SHOW TABLES;
```

- List WordPress Users:
```bash
sudo docker exec -it wordpress wp user list --allow-root
```


### Inception-Specific Auditing (Evaluation Ready)

* **PID 1 Verification:** Ensure the service is running as the primary process (no shell wrappers):

```bash
sudo docker exec -it mariadb ps -p 1 -o comm=
sudo docker exec -it wordpress ps -p 1 -o comm=

```

*Expected output: `mysqld` / `php-fpm` (Success). If it returns `sh`, `bash` or `script.sh`, it is a failure.*

* **Process Health:** Monitor for zombie or orphan processes:

```bash
sudo docker exec -it mariadb ps aux

```

* **Graceful Shutdown Check:** Verify if containers exit correctly (SIGTERM) vs being forced (SIGKILL):

```bash
# Run after 'make stop'
# Mandatory part:
sudo docker inspect mariadb --format '{{.State.ExitCode}}'
sudo docker inspect nginx --format '{{.State.ExitCode}}'
sudo docker inspect wordpress --format '{{.State.ExitCode}}'

# bonus part:
sudo docker inspect static_site --format '{{.State.ExitCode}}'

```

* **Success (0 / 143):** Container closed gracefully.
* **Failure (137):** Container was forced to stop (PID 1 issue or timeout).

### test NGINX -> SSL/TLS
```bash
curl -vI --tlsv1.2 --tls-max 1.3 https://mzolotar.42.fr
```

### Docker Logs
- Display the log for a specific Docker container:
```bash
sudo docker logs <container_name>
```
- Show logs for all Docker containers:
```bash
make logs
```

### Resource Monitoring
```bash
make stats
```
---

## 7. Bonus Management and Debugging

### ✨ Static site

#### Correct operation:
- **Main page:** https://mzolotar.42.fr/static/index.html (or simply https://mzolotar.42.fr/static/).
- **Internal pages:** Check `Developer` and `Playground` links to ensure internal navigation works and assets (CSS/JS) load correctly.

#### Expected nginx error:
Try https://mzolotar.42.fr/stat -> should return 404 error (nginx).

#### Testing Custom Error Pages:
Since we have developed custom error pages in the `static_site` container, we should verify they are served with the correct design and "Back to Home" functionality.

| Error | Test URL / Command | Expected Behavior |
| :--- | :--- | :--- |
| **404 Not Found** | https://mzolotar.42.fr/static/noexists | Displays custom 404 page. |
| **403 Forbidden** | https://mzolotar.42.fr/static/errors/ | Displays custom 403 page (Access denied to folder). |
| **Direct Access** | https://mzolotar.42.fr/static/errors/500.html | Displays the 500 error page design directly. |

> [!TIP]
> If you are testing from the terminal, **always use `curl -k`** to bypass the self-signed certificate warning. If `mzolotar.42.fr` is not working, ensure it's in your `/etc/hosts` or use `localhost` with the correct port if testing internally.

**Validation Checklist:**
1. **Format/CSS:** The error page must have the same dark theme and styles as the rest of the site.
2. **Redirection:** Clicking "Back to Home" on any error page must lead to https://mzolotar.42.fr/static/index.html.
3. **Images/Assets:** Verify that the image in the mandatory/bonus section of the index loads correctly.

> [!NOTE]
> If the error pages appear as plain text or without CSS, ensure that the paths in the HTML files are absolute (e.g., `/static/css/style.css`) and that the NGINX configuration for `static_site` doesn't have the `internal` directive blocking access to the `/errors/` folder during proxying.

### ✨ Adminer

1. Verify that the Adminer container is running
```bash
sudo docker ps | grep adminer
```

2. Health Check (Network Check)
```bash
sudo docker exec adminer curl -I http://localhost:8080
```

3. Verify the connection to MariaDB (crucial)
```bash
sudo docker exec adminer ping -c 3 mariadb
```
Expected Output:
![alt text](/images/image2.png)

4. Browser test
4.1. Open your browser.
4.2. Go to: https://mzolotar.42.fr/adminer/ (or http://mzolotar.42.fr:8080 if you are not using a proxy).
![alt text](/images/image.png)
4.3. The login details are the ones you defined in your setup:
System: `MySQL`
Server: `mariadb` (this is key: use the service name, not localhost)
Username: `$SQL_USER` (your configured user)
Password: `$SQL_PASSWORD` (your password)
Database: `inception_db` 

![alt text](/images/image3.png)

### ✨ FTP server

> [!NOTE]
> `lftp` must be installed on your VM.

1. Create a test file on your local machine:
```bash
echo "Hello Inception" > test.txt
```

2. Upload it to the FTP server using lftp:
```bash
lftp -u <FTP_USER>,<FTP_PASS> localhost -e "put test.txt; quit"
```

3. Verify that the file reached the WordPress container.

```bash
# Verify the file exists inside the WordPress container filesystem
sudo docker exec -it wordpress ls /var/www/html/ | grep test.txt

# Verify the file exists in the shared host volume
# This confirms the data persists correctly in the shared path regardless of the container
ls ~/data/wordpress_data/ | grep test
```

If that `ls` returns `/var/www/html/test.txt`, you've demonstrated the FTP server is working and writing to the shared volume.

The file is uploaded to the FTP container and stored in the shared volume. Even though we send the file to the FTP service, because both the FTP container and the WordPress container are mounted to the same host directory (~/data/wordpress_data), the file becomes immediately accessible to WordPress. This demonstrates the shared volume persistence architecture.



### ✨ Catvisor

> [!NOTE]
> `curl` must be installed on your VM.

1. Health check (server level)

Ensure the container responds from inside the network:
```bash
sudo docker exec catvisor curl -I http://localhost:3000
```

2. Browser test (proxy level)

Open your browser and visit: https://mzolotar.42.fr/catvisor/
If you see your "cats" page or the dashboard, the proxy is working correctly.

3. Logs test (debug level)

If you get a 502 Bad Gateway (common when Nginx cannot connect to the container), check the proxy logs to diagnose the issue:

```bash
sudo docker logs nginx
```

This will show whether Nginx cannot find the container or if the container is refusing the connection.
