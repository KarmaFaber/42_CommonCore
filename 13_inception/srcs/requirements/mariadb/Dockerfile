# Specifies the base image from which you are building
FROM debian:bullseye

# Install MariaDB
RUN apt-get update && apt-get install -y mariadb-server

# Copy MariaDB configuration files
COPY conf/50-server.cnf /etc/mysql/mariadb.conf.d/50-server.cnf

# Copy the setyp script
COPY tools/mariadb_setup.sh /usr/local/bin/mariadb_setup.sh

RUN chmod +x /usr/local/bin/mariadb_setup.sh

# Open the database port
EXPOSE 3306

# Run the script when the container starts
ENTRYPOINT ["/usr/local/bin/mariadb_setup.sh"]
