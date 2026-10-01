*This project has been created as part of the 42 curriculum by mzolotar.*

# Inception

## Description
The goal of this project is to broaden your knowledge of system administration by using Docker. You will virtualize several Docker images, creating a complete infrastructure composed of multiple services (Nginx, MariaDB, and WordPress) that must run in separate containers, communicate through a private network, and persist data using volumes.

## Project Description & Design Choices
This project implements a **LEMP-like stack** (Linux, Nginx, MariaDB, PHP) using a microservices architecture.
- **Microservices:** Each service (Nginx, MariaDB, WordPress) runs in its own container to follow the "one service per container" principle.
- **Base Image:** All containers are built using **Debian Bullseye** for stability and security.
- **Initialization:** We use custom entrypoint scripts and **WP-CLI** to automate the setup, ensuring the site is ready on the first launch.

![alt text](/images/mandatory.png)

### 🚀 Why this startup order?
mariadb ➡️ wordpress ➡️ nginx
The infrastructure follows a logic of dependencies:
- MariaDB first: WordPress cannot initialize or configure itself without a database to connect to. The database must be up and running to accept the initial configuration.
- WordPress second: Once the database is ready, WordPress can run its setup (via WP-CLI) and start the PHP-FPM service on port 9000.
- Nginx last: Nginx acts as a Reverse Proxy. It requires the WordPress service to be alive so it can forward PHP requests via FastCGI. If WordPress isn't there, Nginx will have nothing to serve.

## Instructions
1. Clone the repository.
2. Navigate to the root folder.
3. Run `make`.
4. Access the site at `https://mzolotar.42.fr`.

## Technical Comparisons
- Virtual Machines vs Docker: 
	* Virtual Machines: Emulate a full hardware stack, including a Guest OS. They are heavy, slow to boot, and consume significant resources.
	* Docker: Uses containerization to share the Host OS Kernel. Containers are lightweight, start in seconds, and only package the application and its dependencies.

- Secrets vs Environment Variables:
	* Environment Variables: Best for non-sensitive configuration (like database names or hostnames). They are visible in the process tree and docker inspect.
	* Secrets: Specifically designed for sensitive data (passwords, keys). In a professional environment (like Docker Swarm), they are encrypted at rest and only decrypted into memory when the container needs them.

- Docker Network vs Host Network:
	* Docker Network (Bridge): Creates an isolated virtual network for your containers. They can only talk to each other using internal DNS (service names). This is the mandatory approach for Inception.
	* Host Network: The container shares the host’s IP and ports directly. This breaks isolation and is strictly forbidden in this project.

- Docker Volumes vs Bind Mounts:
	* Docker Volumes: Managed entirely by Docker in a specific area of the host's storage. They are the preferred way to persist data.
	* Bind Mounts: Maps a specific path on the host (like /home/user/data) to a path inside the container. They depend on the host's file system structure.

## What is docker? 
Docker is a containerization platform that enables developers and teams to package, develop, test, ship, deploy, and run applications in lightweight, standalone containers. These containers include everything needed to run an application—such as code, runtime, libraries, and configuration files—ensuring consistency across different environments.

## What are a Container?
A container is a lightweight, standalone, and executable package that includes everything needed to run an application—such as code, runtime, libraries, environment variables, and configuration files. Containers are isolated from each other and from the host system, ensuring that each application component runs in its own environment without interfering with others.

![alt text](/images/docker_container_lifecycle.png)

## What is a docker image?
A Docker image is a read-only template that contains the instructions for creating a Docker container. It includes everything needed to run an application, such as the application code, runtime, libraries, environment variables, and configuration files. Images are often based on other images, with additional customizations layered on top.

## What is a docker service?
In Docker Compose, a service is an abstract definition of a computing resource within an application that can be scaled or replaced independently from other components. Each service is backed by one or more containers, all created from the same Docker image and configuration. Services are defined in the Compose file under the top-level services section, and each service definition specifies how its containers should be run, including build instructions, runtime arguments, and deployment constraints.


## What is a docker volume?
When working with containers, it's crucial to understand how data is stored, as container data is ephemeral by default. A Docker volume is a persistent storage mechanism that is completely managed by the Docker engine. As you can see in the diagram above (left), a Docker container can interact with a specialized 'volume' that is physically stored in a secure, Docker-managed area of the host's file system (under docker engine).

This key distinction between a container and a volume creates persistence. As the right side of the diagram illustrates, when containers are removed (even forcefully deleted), the volume and its contents remain. This is because the volume is not tied to the container's lifecycle. Data created, modified, or preserved in a volume exists independently, allowing new containers to attach to it and inherit the state. This is fundamental for stateful applications like databases, where ensuring data preserved across container restarts, updates, and accidental deletions is not optional. The other method, a bind mount (diagram right), shares a direct directory from the host and is often used for development but is less manageable than Docker volumes.

![alt text](/images/persitency.png)


## How the Docker engine works?
The Docker Engine is the core open-source technology that powers the creation and management of containers. It follows a client-server architecture:

- Docker Daemon (dockerd): The server-side process that manages Docker objects like images, containers, networks, and volumes.
- REST API: The bridge that allows the client to communicate with the daemon.
- Docker CLI: The command-line interface (e.g., docker build, docker compose) that users interact with to send instructions.

In this project, the Docker Engine ensures that each service (Nginx, MariaDB, WordPress) runs in an isolated environment using the host's kernel, optimizing resource usage compared to traditional virtual machines.


## What is PID 1 and why does it matter?

In a Docker container, the process with PID 1 (Process ID 1) has a unique responsibility: it must handle system signals (like `SIGTERM` for graceful shutdowns) and reap "zombie" processes.

In this project, we ensure the main service (Nginx, MariaDB, or PHP-FPM) runs as PID 1 by using the `exec` command in our entrypoint scripts. This allows:
1. Proper Signal Handling: When running `docker stop`, the service receives the signal directly and shuts down safely without data loss.
2. Avoiding "Hacks": We avoid using infinite loops like `tail -f` or `sleep infinity`, which are prohibited by the subject because they prevent the container from reacting correctly to the service's lifecycle.

Within Docker, each container runs in its own PID namespace. This means that the process started by the dockerfile will always be PID 1, and PIDs will count upwards from there.

## What is a docker-compose?
Docker Compose is a tool for defining and running multi-container applications.
Compose simplifies the control of your entire application stack, making it easy to manage services, networks, and volumes in a single YAML configuration file. Then, with a single command, you create and start all the services from your configuration file -> `docker-compose.yml`

Compose works in all environments - production, staging, development, testing, as well as CI workflows. It also has commands for managing the whole lifecycle of your application:

- Start, stop, and rebuild services.
- View the status of running services.
- Stream the log output of running services.
- Run a one-off command on a service.

## AI Usage Disclosure

**Gemini** (Google’s Large Language Model) was integrated into the development of this project as a **Senior Infrastructure Mentor**.

Instead of providing "copy-paste" solutions, the AI was configured from the start to act as a pedagogical guide, focusing on the following areas:

* **Conceptual Foundations:** The AI acted as a theory-first mentor, ensuring a deep understanding of system administration, networking, and Docker fundamentals before any code was written.
* **Architecture & Security:** It assisted in reasoning through network design, volume hierarchy, and the implementation of the "Least Privilege" policy, specifically regarding SSL/TLS (Port 443) and environment variable management.
* **Best Practices & Anti-Patterns:** The development process was guided by the avoidance of "hacky patches." The AI challenged technical decisions regarding **PID 1**, Unix signals, and proper service orchestration to ensure project stability.
* **Defense Preparation:** It performed continuous "control questions" to verify concept comprehension and simulated evaluation scenarios to ensure the infrastructure's portability and strict compliance with the 42 subject and evaluation criteria.

The final result is a product of human reasoning supported by AI-driven technical auditing, prioritizing learning over mere automation.


## 📕 Main Resources
- [Docker Documentation](https://docs.docker.com/)
- [Nginx Official Docs](https://nginx.org/en/docs/)
- [WP-CLI Handbook](https://make.wordpress.org/cli/handbook/)

- [MariaDB oficial doc.](https://mariadb.com/docs)
- [Import-export databases](https://www.interserver.net/tips/kb/import-export-databases-mysql-command-line/) 
- [50-server.cnf file](https://github.com/sismics/docker-mariadb/blob/master/etc/mysql/mariadb.conf.d/50-server.cnf)

- [WordPress useful commands.](https://developer.wordpress.org/cli/commands/)
- [WordPress](https://docs.digitalocean.com/products/marketplace/catalog/wordpress/)
- [www.conf file](https://github.com/php/php-src/blob/master/sapi/fpm/www.conf.in)


---
## Bonus part

### ✨ Static Site:

Access the site at https://mzolotar.42.fr/static/ or https://mzolotar.42.fr/static/index.html


### ✨ Adminer:
Adminer is a lightweight yet comprehensive web-based tool for managing databases (such as MySQL, PostgreSQL, Oracle, and SQLite). Its main advantage is that it consists of a single PHP file, making it a fast, secure, and easy-to-install alternative to bulkier options like phpMyAdmin. 
📕 [oficial doc adminer](https://www.adminer.org/)

Go to: https://mzolotar.42.fr/adminer/

![alt text](/images/bonus_3_services.png)


###  ✨ ftp server
An FTP server, or File Transfer Protocol server, is a technology used to transfer files over a network, typically the Internet. It operates on a client-server model, where an FTP server stores files and allows users to connect to upload or download files.

📕 [oficial doc vsftpd](http://vsftpd.beasts.org/vsftpd_conf.html/)
📕 [vsftpd.conf(5) - Linux man page](https://linux.die.net/man/5/vsftpd.conf)

![alt text](/images/bonus_ftp.png)


###  ✨ Catvisor
It is an open-source tool from Google designed to monitor containers (such as Docker). It analyzes and collects data on container resource usage (CPU, memory, disk, network) in real time, helping you monitor the performance of your applications.

To make the monitoring real, Catvisor must talk to the Docker daemon through the mounted `/var/run/docker.sock` socket. We grant Apache access to that socket at runtime by matching the socket GID and adding `www-data` to the correct group, so the dashboard can read live container data instead of showing a fake status.

📕 [oficial doc Catvisor](https://github.com/google/cadvisor)

![alt text](/images/bonus_catvisor.png)
