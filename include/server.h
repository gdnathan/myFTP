/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** server
*/

#pragma once
#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <string.h>

typedef enum
{
    ERROR = 84,
    EXIT = 0,
    OK = 0,
} status_t;

typedef struct
{
    int port;
    char *path;
    int socket;
    struct sockaddr_in adress;
} network_t;

typedef struct
{
    network_t client;
} server_t;

typedef struct
{
    char *command;
    char *argument;
} line_t;

void set_server_addr(network_t *server);
status_t open_socket(network_t *server);
server_t init_server(network_t client);
line_t parse_line(char *src);
char *readline(int fd);
