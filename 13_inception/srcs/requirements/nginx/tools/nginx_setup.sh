#!/bin/bash
set -e

# 1. Create directory for SSL certificates
mkdir -p /etc/nginx/ssl

# 2. Generate SSL Certificate (Self-signed)
# -x509: output a self-signed certificate
# -nodes: no DES, don't encrypt the private key
# -days 365: valid for a year
# -subj: automated filling of the certificate info
if [ ! -f /etc/nginx/ssl/mzolotar.crt ]; then
    openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
        -keyout /etc/nginx/ssl/mzolotar.key \
        -out /etc/nginx/ssl/mzolotar.crt \
        -subj "/C=ES/ST=Malaga/L=Malaga/O=42/OU=mzolotar/CN=mzolotar.42.fr"
    echo " ✅ Nginx: SSL certificate generated."
fi

# 3. Start Nginx in foreground
echo " ✅ Nginx: starting..."
exec nginx -g "daemon off;"
