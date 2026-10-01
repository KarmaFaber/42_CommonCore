# Specifies the base image from which you are building
FROM debian:bullseye

# Install dependencies statically during build time
RUN apt-get update && apt-get install -y \
    php-fpm \
    php-mysql \
    wget \
    && rm -rf /var/lib/apt/lists/*

# Download Adminer
RUN mkdir -p /var/www/html/adminer
RUN wget "http://www.adminer.org/latest.php" -O /var/www/html/adminer/index.php
RUN chown -R www-data:www-data /var/www/html/adminer
RUN chmod 755 /var/www/html/adminer/index.php

# Expose the port
EXPOSE 8080

# Serve using PHP's built-in web server
WORKDIR /var/www/html/adminer
CMD ["php", "-S", "0.0.0.0:8080"]