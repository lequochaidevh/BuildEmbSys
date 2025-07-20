#!/bin/bash

USER_ID=${HOST_UID:-1000}
GROUP_ID=${HOST_GID:-1000}
USER_NAME=${HOST_USER:-devuser}

if ! getent group $GROUP_ID >/dev/null; then
    groupadd -g $GROUP_ID $USER_NAME
fi

if ! id -u $USER_NAME >/dev/null 2>&1; then
    useradd -m -u $USER_ID -g $GROUP_ID -s /bin/bash $USER_NAME
    echo "$USER_NAME ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers
fi

exec su - $USER_NAME
