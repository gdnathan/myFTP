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
#include <unistd.h>

typedef struct
{
    fd_set readfds;
    fd_set save;
    int max;
} fds_t;

status_t handle_auth(status_t (*)(client_t *, char *), client_t *, line_t);

status_t handle_command(client_t *client)
{
    line_t line = parse_line(readline(client->controlSocket));
    status_t status = OK;
    int i = 0;

    while (commands[i]) {
        if (strcmp(commands[i], line.command) == 0) {
            status = handle_auth(functions[i], client, line);
            break;
        }
        i++;
    }
    if (commands[i] == NULL) {
        fprintf(stderr, "Unknown command: %s.\n", line.command);
        ftpsend(client->controlSocket, "xxx", "Unknown command.");
    } if (status == ERROR) {
        fprintf(stderr, "An error occured while executing command %s.\n",
            line.command);
    }
    return status;
}

status_t handle_fd(int fd, fds_t *fds, network_t *server, client_t **head)
{
    status_t status = OK;

    if (fd == server->socket) {
        int accept_socket = accept(server->socket, NULL, NULL);
        FD_SET(accept_socket, &fds->save);
        new_client(accept_socket, head, server);
        if (accept_socket > fds->max)
            fds->max = accept_socket;
    } else {
        status = handle_command(find_client(fd, head));
        if (status == DISCONNECT) {
            FD_CLR(fd, &fds->save);
            delete_client(fd, head);
        } else if (status == KILL) {
            return EXIT;
        }
    }
    return OK;
}

status_t filter_fds(fds_t *fds, network_t *server, client_t **head)
{
    status_t status = OK;
    for (int fd = 0; fd <= fds->max; fd++) {
        if (FD_ISSET(fd, &fds->readfds)) {
            status = handle_fd(fd, fds, server, head);
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
    client_t *head = NULL;

    FD_ZERO(&fds.readfds);
    FD_ZERO(&fds.save);
    FD_SET(server->socket, &fds.save);
    fds.max = server->socket;
    do {
        fds.readfds = fds.save;
        if (select(fds.max + 1, &fds.readfds, NULL, NULL, NULL)) {
            status = filter_fds(&fds, server, &head);
        }
        if (status == EXIT) {
            close(server->socket);
            break;
        }
    } while (1);
    return OK;
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
