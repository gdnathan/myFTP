/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** server
*/

#include "server.h"
#include "minishell.h"
#include <arpa/inet.h>
#include <stdbool.h>
#include <sys/select.h>

typedef struct
{
    fd_set readfds;
    fd_set save;
    int max;
} fds_t;

status_t handle_command(int socket)
{
    line_t line = parse_line(readline(socket));
    status_t status = OK;
    server_t server = init_server(socket);
    int i = 0;

    while (commands[i]) {
        if (strcmp(commands[i], line.command) == 0) {
            status = (functions[i])(server, line.argument);
            break;
        }
        i++;
    }
    if (commands[i] == NULL)
        fprintf(stderr, "Unknown command: %s.\n", line.command);
    if (status == ERROR)
            fprintf(stderr, "An error occured while executing command %s.\n",
                line.command);
    return status;
}

status_t handle_fd(int fd, fds_t *fds, network_t *server)
{
    status_t status = OK;

    if (fd == server->socket) {
        int accept_socket = accept(server->socket, NULL, NULL);
        FD_SET(accept_socket, &fds->save);
        if (accept_socket > fds->max)
            fds->max = accept_socket;
    } else {
        status = handle_command(fd);
        if (status == DISCONNECT) {
            FD_CLR(fd, &fds->save);
            close(fd);
        } else if (status == KILL) {
            return EXIT;
        }
    }
    return OK;
}

status_t filter_fds(fds_t *fds, network_t *server)
{
    status_t status = OK;
    for (int fd = 0; fd <= fds->max; fd++) {
        if (FD_ISSET(fd, &fds->readfds)) {
            status = handle_fd(fd, fds, server);
        }
        if (status == EXIT)
            return EXIT;
    }
    return OK;
}

status_t server_loop(network_t *server)
{
    network_t client;
    fds_t fds;
    status_t status;

    FD_ZERO(&fds.readfds);
    FD_ZERO(&fds.save);
    FD_SET(server->socket, &fds.save);
    fds.max = server->socket;
    do {
        fds.readfds = fds.save;
        if (select(fds.max + 1, &fds.readfds, NULL, NULL, NULL)) {
            status = filter_fds(&fds, server);
        }
        if (status == EXIT) {
            close(server->socket);
            break;
        }
    } while (1);
}

status_t ftp_server(network_t *server)
{
    if (open_socket(server) != OK)
        return ERROR;
    set_server_addr(server);
    if (bind(server->socket, (struct sockaddr *)&server->adress,
            sizeof(server->adress)) != 0)
        return ERROR;
    listen(server->socket, 10);
    return server_loop(server);
}
