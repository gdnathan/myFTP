/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** init_server
*/

#include "server.h"

status_t open_socket(network_t *server)
{
    server->socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server->socket < 0) {
    printf("bite\n");
        return ERROR;
    }
    return OK;
}

void set_server_addr(network_t *server)
{
    server->adress.sin_family = AF_INET;
    server->adress.sin_port = htons(server->port);
    server->adress.sin_addr.s_addr = INADDR_ANY;
}
