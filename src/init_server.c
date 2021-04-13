/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** init_server
*/

#include "server.h"
#include <unistd.h>

status_t open_socket(network_t *server)
{
    server->socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server->socket < 0) {
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

char *readline(int fd)
{
    char *line = malloc(sizeof(char) * 256);
    int i = 0;
    char *tmp = malloc(sizeof(char) * 1);
    int status = 1;

    while (status != 0 && status != -1 && i < 256) {
        status = read(fd, tmp, 1);
        if (*tmp == '\n')
            break;
        line[i++] = *tmp;
    }
    return line;
}

line_t parse_line(char *src)
{
    int i = 0;
    line_t line;

    while (src[i] != '\0' || src[i] != ' ')
        i++;
    line.command = strndup(src, i);
    if (src[i] == ' ') {
        src += i + 1;
        line.argument = strdup(src);
    } else {
        line.argument = "";
    }
    return line;
}

server_t init_server(network_t client)
{
    server_t server;

    server.client = client;
    return server;
}
