/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** show
*/

#include "server.h"
#include <unistd.h>

status_t pwd(client_t *client, char *param)
{
    ftpsend(client->controlSocket, "257", client->path);
    return OK;
}

status_t list(client_t *client, char *param)
{
    return OK;
}
