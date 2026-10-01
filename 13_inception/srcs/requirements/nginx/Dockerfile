# Specifies the base image from which you are building
FROM debian:bullseye

# Install Nginx and OpenSSL
RUN apt-get update && apt-get install -y \
    nginx \
    openssl \
    && rm -rf /var/lib/apt/lists/*

# Copy the configuration file
# We remove the default one and link ours
COPY conf/nginx.conf /etc/nginx/conf.d/default.conf

# Copy setup script
COPY tools/nginx_setup.sh /usr/local/bin/nginx_setup.sh
RUN chmod +x /usr/local/bin/nginx_setup.sh

# Port 443 for HTTPS
EXPOSE 443

# Execute setup script
ENTRYPOINT ["/usr/local/bin/nginx_setup.sh"]
