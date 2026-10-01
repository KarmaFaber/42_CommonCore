# User Documentation

## Services Provided
This stack provides a fully functional **WordPress** website served through an **Nginx** web server with **TLS 1.3** encryption, using **MariaDB** as the backend database.

## Getting Started
To launch the project, use the provided Makefile:
- **Start:** `make`
- **Stop:** `make stop`
- **Full Cleanup:** `make fclean` (Warning: this deletes all data).

## Accessing the Platform

### Mandatory Part
- **Website:** https://mzolotar.42.fr
- **Admin panel:** https://mzolotar.42.fr/wp-admin/
- **Example user page (comments):** https://mzolotar.42.fr/?p=1

### Bonus Part
- **Adminer (DB GUI):** https://mzolotar.42.fr/adminer/
- **Static demo site:** https://mzolotar.42.fr/static/  (equivalent to /static/index.html)
- **Catvisor (monitor):** https://mzolotar.42.fr/catvisor/ — panel that displays Docker status and basic runtime info (requires Docker socket access in the container).

> [!NOTE]
> Note: the bonus links above are functional. The ability to reach those endpoints from the bonus pages is a combination of two things:
> - the server routing defined in Nginx (see `srcs/requirements/nginx/conf/nginx.conf`), which exposes the bonus paths; and
> - small header updates in the bonus pages so `Static`, `Catvisor` and `Adminer` are linked from both the static site and the Catvisor dashboard (see `srcs/requirements/bonus/static_site/tools/public/index.html` and `srcs/requirements/bonus/catvisor/app/index.html`).




## Credentials Management

For security reasons, passwords and usernames are not hardcoded into the system. You can manage them in two ways:

1.  **Direct Configuration (Advanced):** All initial credentials (database, admin user, and regular user) are stored in the `srcs/.env` file on the host machine. If you need to check the original setup, you can find them there.
2.  **WordPress Admin Panel (User Friendly):** Once the site is running, an administrator can change any user password (including their own) without touching a single line of code:
    - Log in to https://mzolotar.42.fr/wp-admin/.
    - Navigate to the **"Users"** section in the left sidebar.
    - Click on **"All Users"** and select the profile you wish to edit.
    - Scroll down to the **"Account Management"** section and click **"Set New Password"**.
    - Click **"Update Profile"** at the bottom to save the changes.
    
## Security & Connection

To ensure the integrity and privacy of your data, the platform is configured with a **Strict Security Policy**:

- **Exclusive HTTPS Access:** The website is only accessible via **Port 443** (HTTPS) using TLS 1.3 encryption. 
- **Non-Secure Traffic Blocked:** Any attempt to connect via **Port 80** (standard HTTP) is strictly blocked or ignored by the firewall. This ensures that no unencrypted data ever leaves the server. 
- **Certificate:** If your browser shows a "Connection not private" warning, it is because we use a **Self-Signed Certificate** for development. You can safely click on "Advanced" and "Proceed" to access your local site.

## Health Check
To verify that all services are running correctly:
1. Run `make status` (or `docker ps`).
2. All containers (`nginx`, `wordpress`, `mariadb`, bonus part containers) should show a status of **Up**.
3. Resource Monitoring: `make stats`