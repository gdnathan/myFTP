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
status_t user(server_t, char *param);
status_t pass(server_t, char *param);

// move througt server files
status_t cwd(server_t, char *param);
status_t cdup(server_t, char *param);

// show files
status_t pwd(server_t, char *param);
status_t list(server_t, char *param);

// idk
status_t dele(server_t, char *param);

// server interaction
status_t quit(server_t, char *param);
status_t help(server_t, char *param);
status_t noop(server_t, char *param);
status_t kill(server_t, char *param);

// data transfer mode
status_t pasv(server_t, char *param);
status_t port(server_t, char *param);

// data transfer
status_t retr(server_t, char *param);
status_t stor(server_t, char *param);

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


static status_t (*functions[15])(server_t, char *param) = {
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
