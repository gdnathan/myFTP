/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** interaction
*/

#include "server.h"

status_t quit(client_t *client, char *param)
{
    return DISCONNECT;
}

status_t help(client_t *client, char *param)
{
    ftpsend(client->controlSocket, "214", "Help message (or not lol)");
    return OK;
}

status_t noop(client_t *client, char *param)
{
    ftpsend(client->controlSocket, "200", "Command okay.");
    return OK;
}

status_t kill(client_t *client, char *param)
{
    return KILL;
}
