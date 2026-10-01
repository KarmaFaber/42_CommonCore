#!/bin/sh
set -e

DOCKER_SOCK=/var/run/docker.sock

if [ -S "$DOCKER_SOCK" ]; then
    SOCK_GID="$(stat -c '%g' "$DOCKER_SOCK")"
    SOCK_GROUP="$(getent group "$SOCK_GID" | cut -d: -f1 || true)"

    if [ -z "$SOCK_GROUP" ]; then
        SOCK_GROUP="dockersock"
        if ! getent group "$SOCK_GROUP" >/dev/null 2>&1; then
            groupadd -g "$SOCK_GID" "$SOCK_GROUP"
        fi
    fi

    usermod -aG "$SOCK_GROUP" www-data
fi

exec apache2-foreground
