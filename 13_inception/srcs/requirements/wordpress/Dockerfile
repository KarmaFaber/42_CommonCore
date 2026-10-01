# Specifies the base image from which you are building
FROM debian:bullseye

# Install dependencies statically during build time
RUN apt-get update && apt-get install -y \
    php7.4-fpm \
    php-mysql \
    curl \
    nano \
    && rm -rf /var/lib/apt/lists/*

# Install WP-CLI (WordPress Command Line Interface)
RUN curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar \
    && chmod +x wp-cli.phar \
    && mv wp-cli.phar /usr/local/bin/wp

# Copy PHP-FPM configuration
COPY conf/www.conf /etc/php/7.4/fpm/pool.d/www.conf

# Create the folder for PHP-FPM to store its socket/pid files
RUN mkdir -p /run/php

# Copy the setup scripts and give execution permissions
COPY tools/wp_setup.sh /usr/local/bin/wp_setup.sh
RUN chmod +x /usr/local/bin/wp_setup.sh

# Move to the web root directory
WORKDIR /var/www/html/

# Port 9000 for PHP-FPM communication
EXPOSE 9000

# Launch the setup script
ENTRYPOINT ["/usr/local/bin/wp_setup.sh"]