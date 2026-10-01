#!/bin/bash
set -e

mysqld_safe --skip-grant-tables &

echo " ⌛ MariaDB: waiting for local server socket..."
until mariadb -u root -e "SELECT 1;" >/dev/null 2>&1; do
	sleep 1
done
echo " ✅ MariaDB: bootstrap server ready."

mariadb -u root << EOF
FLUSH PRIVILEGES;
CREATE DATABASE IF NOT EXISTS \`${SQL_DATABASE}\`;
CREATE USER IF NOT EXISTS \`${SQL_USER}\`@'%' IDENTIFIED BY '${SQL_PASSWORD}';
GRANT ALL PRIVILEGES ON \`${SQL_DATABASE}\`.* TO \`${SQL_USER}\`@'%';
ALTER USER 'root'@'localhost' IDENTIFIED BY '${SQL_ROOT_PASSWORD}';
FLUSH PRIVILEGES;
EOF

mysqladmin -u root -p"${SQL_ROOT_PASSWORD}" shutdown
exec mysqld