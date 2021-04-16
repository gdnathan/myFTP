/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** minishell
*/

#pragma once

#include "server.h"
#include <stdlib.h>

// connection
status_t user(client_t *client, char *param);
status_t pass(client_t *client, char *param);

// move througt server files
status_t cwd(client_t *client, char *param);
status_t cdup(client_t *client, char *param);

// show files
status_t pwd(client_t *client, char *param);
status_t list(client_t *client, char *param);

// idk
status_t dele(client_t *client, char *param);

// server interaction
status_t quit(client_t *client, char *param);
status_t help(client_t *client, char *param);
status_t noop(client_t *client, char *param);
status_t kill(client_t *client, char *param);

// data transfer mode
status_t pasv(client_t *client, char *param);
status_t port(client_t *client, char *param);

// data transfer
status_t retr(client_t *client, char *param);
status_t stor(client_t *client, char *param);

// clang-format off
static char* commands[15] = {
    "USER",
    "PASS",
    "CWD",
    "CDUP",
    "QUIT",
    "DELE",
    "PWD",
    "PASV",
    "PORT",
    "HELP",
    "NOOP",
    "RETR",
    "STOR",
    "LIST",
    "KILL"
};


static status_t (*functions[15])(client_t *client, char *param) = {
    user,
    pass,
    cwd,
    cdup,
    quit,
    dele,
    pwd,
    pasv,
    port,
    help,
    noop,
    retr,
    stor,
    list,
    kill
};
// clang-format on
