/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** server
*/

#include "server.h"
#include "minishell.h"
#include <arpa/inet.h>

void handle_command(network_t client)
{
    line_t line = parse_line(readline(client.socket));
    status_t status;
    server_t server = init_server(client);
    int i = 0;

    while (commands[i]) {
        if (strcmp(commands[i], line.command)) {
            status = functions[i](server, line.argument);
            break;
        }
        i++;
    }
    if (commands[i] == NULL) {
        fprintf(stderr, "Unknown command: %s.\n", line.command);
    } else if (status == ERROR) {
        fprintf(stderr, "An error occured while executing command %s.\n",
            line.command);
    }
}

status_t server_loop(network_t *server)
{
    network_t client;
    printf("port listening: %d\n", server->port);
    pid_t process;

    for (;;) {
        printf("Waiting for connection...\n");
        client.socket = accept(server->socket, NULL, NULL);
        process = fork();
        if (process == -1) {
            fprintf(stderr, "Fatal error: fork()\n");
            return ERROR;
        }
        if (process == 0) {
            printf("connection established.\n");
            handle_command(client);
            return EXIT;
        }
    }
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
