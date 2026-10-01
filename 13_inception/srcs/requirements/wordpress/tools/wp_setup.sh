#!/bin/bash
set -e

# 1. Wait for MariaDB to be ready
sleep 10

# 2. Start setup if not already installed
if [ ! -f /var/www/html/wp-config.php ]; then
    echo "WordPress: Downloading core files..."
    wp core download --allow-root

    echo "WordPress: Creating wp-config.php..."
    wp config create \
        --dbname="$SQL_DATABASE" \
        --dbuser="$SQL_USER" \
        --dbpass="$SQL_PASSWORD" \
        --dbhost="$SQL_HOST" \
        --allow-root

    echo "WordPress: Installing and creating Admin..."
    wp core install \
        --url="$DOMAIN_NAME" \
        --title="$WP_TITLE" \
        --admin_user="$WP_ADMIN_USER" \
        --admin_password="$WP_ADMIN_PASS" \
        --admin_email="$WP_ADMIN_EMAIL" \
        --allow-root

    echo "WordPress: Creating secondary user..."
    wp user create \
        "$WP_USER" \
        "$WP_USER_EMAIL" \
        --user_pass="$WP_USER_PASS" \
        --role=author \
        --allow-root
    
    echo "WordPress: Setup finished!"
else
    echo "WordPress: Already installed."
fi

# 3. Start PHP-FPM in foreground replacing the shell process (PID 1 management)
echo "Starting PHP-FPM on port 9000..."
exec php-fpm7.4 -F