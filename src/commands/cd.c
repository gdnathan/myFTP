/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** cd
*/

#include "server.h"

status_t cwd(client_t *client, char *param)
{
    client->path = param;
    ftpsend(
        client->controlSocket, "250", "Requested file action okay, completed.");
    return OK;
}

status_t cdup(client_t *client, char *param)
{
    int cut = 0;
    int i = 0;
    char *cpy = NULL;
    printf("in\n");

    if (strcmp(client->path, "/") == 0) {
        ftpsend(client->controlSocket, "200", "Command okay..");
        return OK;
    }
    while (client->path[i]) {
        if (client->path[i] == '/')
            cut = i;
        i++;
    }
    cpy = strndup(client->path, cut);
    printf("current: %s\n", cpy);
    free(client->path);
    client->path = cpy;
    ftpsend(client->controlSocket, "200", "Command okay.");
    return OK;
}
