# Specifies the base image from which you are building
FROM debian:bullseye

# Install
RUN apt-get update && apt-get install -y vsftpd passwd && rm -rf /var/lib/apt/lists/*

# Copy the configuration file
COPY conf/vsftpd.conf /etc/vsftpd.conf
RUN chmod 644 /etc/vsftpd.conf

# Copy the setup script to create the user and start vsftpd
COPY tools/setup.sh /usr/local/bin/setup.sh
RUN chmod +x /usr/local/bin/setup.sh

# Port 21 for FTP and 21000-21010 for passive mode
EXPOSE 21 21000-21010

# Execute setup script
ENTRYPOINT ["/usr/local/bin/setup.sh"]