# Use a lightweight PHP-Apache image
FROM php:8.2-apache

# Install curl and the Docker CLI to allow monitoring of other containers
RUN apt-get update && apt-get install -y curl && \
    curl -fsSL https://get.docker.com -o get-docker.sh && sh get-docker.sh && \
    rm -rf /var/lib/apt/lists/*

# Copy the dashboard application into the Apache web directory
COPY app/ /var/www/html/

# Add a runtime entrypoint that grants Apache access to the mounted Docker socket
COPY tools/entrypoint.sh /usr/local/bin/catvisor-entrypoint.sh
RUN chmod +x /usr/local/bin/catvisor-entrypoint.sh

# Configure Apache to listen on port 3000 instead of 80
RUN sed -i 's/80/3000/g' /etc/apache2/ports.conf /etc/apache2/sites-available/000-default.conf

# Expose the dashboard port
EXPOSE 3000

# Start the Apache server in the foreground
ENTRYPOINT ["/usr/local/bin/catvisor-entrypoint.sh"]