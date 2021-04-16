/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** connection
*/

#include "server.h"

// verry secure authentification
status_t user(client_t *client, char *param)
{
    if (strcmp(param, "Anonymous") == 0) {
        client->username = strdup(param);
        ftpsend(client->controlSocket, "331", "User name okay, need password.");
        return OK;
    }
    ftpsend(client->controlSocket, "xxx", "Error");
    return ERROR;
}

status_t pass(client_t *client, char *param)
{
    if (strcmp(client->username, "Anonymous") == 0 && param == NULL) {
        ftpsend(client->controlSocket, "230", "User logged in, proceed.");
        client->auth = true;
    } else {
        ftpsend(client->controlSocket, "xxx", "Error.");
        client->username = NULL;
        return ERROR;
    }
    return OK;
}
