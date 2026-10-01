#!/bin/bash

if ! id "$FTP_USER" &>/dev/null; then
    useradd -m -d /var/www/html -s /bin/bash "$FTP_USER"
fi

echo "$FTP_USER:$FTP_PASS" | chpasswd

chown -R "$FTP_USER:$FTP_USER" /var/www/html
mkdir -p /var/run/vsftpd/empty

exec vsftpd /etc/vsftpd.conf