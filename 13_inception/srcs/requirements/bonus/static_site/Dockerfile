# Specifies the base image from which you are building (Debian stable)
FROM debian:bullseye

# Install NGINX for serving the static files and clean apt cache
RUN apt-get update && apt-get install -y \
    nginx \
    && rm -rf /var/lib/apt/lists/*

# Copy your customized static NGINX configuration
COPY conf/nginx.conf /etc/nginx/conf.d/default.conf

# Create the folder where the HTML files will live
RUN mkdir -p /var/www/static

# Copy your local web assets into the container's web root
COPY tools/public/ /var/www/static/

# Expose the internal port for the Docker network
EXPOSE 8081

# Start NGINX in the foreground so the container stays alive (PID 1 management)
CMD ["nginx", "-g", "daemon off;"]