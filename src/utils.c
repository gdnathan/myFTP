/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** utils
*/

#include "server.h"
#include <unistd.h>

status_t ftpsend(int socket, char *code, char *comment)
{
    char *msg = calloc(256, sizeof(char));
    strcat(msg, code);
    if (comment) {
        strcat(msg, " ");
        strcat(msg, comment);
    }
    strcat(msg, "\r\n");
    if (write(socket, msg, strlen(msg)) == -1)
        return ERROR;
    return OK;
}
