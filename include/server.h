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
#include <stdbool.h>

typedef enum
{
    ERROR = 84,
    OK = 0,
    EXIT = 1,
    KILL = 2,
    DISCONNECT = 3,
} status_t;

typedef struct
{
    int port;
    char *path;
    int socket;
    struct sockaddr_in adress;
} network_t;

typedef struct client
{
    bool auth;
    char *username;
    char *password;
    char *path;
    int controlSocket;
    int dataSocket;
    struct client *next;
    struct client *prev;
} client_t;

typedef struct
{
    char *command;
    char *argument;
} line_t;

void set_server_addr(network_t *server);
status_t open_socket(network_t *server);
line_t parse_line(char *src);
char *readline(int fd);

void new_client(int socket, client_t **head, network_t *server);
void delete_client(int socket, client_t **head);
client_t *find_client(int socket, client_t **head);
status_t ftpsend(int socket, char *code, char *msg);
