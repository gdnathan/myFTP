/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** interaction
*/

#include "server.h"

status_t quit(server_t server, char *param)
{
    return DISCONNECT;
}

status_t help(server_t server, char *param)
{
    return OK;
}

status_t noop(server_t server, char *param)
{
    return OK;
}

status_t kill(server_t server, char *param)
{
    return KILL;
}
