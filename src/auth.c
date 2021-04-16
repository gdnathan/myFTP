/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** auth
*/

#include "server.h"

status_t handle_auth(
    status_t (*func)(client_t *, char *), client_t *client, line_t line)
{
    if (strcmp(line.command, "PASS") == 0) {
        if (!client->username) {
            ftpsend(client->controlSocket, "332", "Need account for login");
            return ERROR;
        } else if (client->auth == true) {
            ftpsend(client->controlSocket, "xxx", "Already connected");
            return ERROR;
        }
    } else if (strcmp(line.command, "USER") == 0) {
        if (client->auth) {
            ftpsend(client->controlSocket, "xxx", "Already connected");
            return ERROR;
        }
    } else if (client->auth == false) {
        ftpsend(client->controlSocket, "xxx",
            "Need to be login to use this command");
        return ERROR;
    }
    return (*func)(client, line.argument);
}
