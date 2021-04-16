/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** data_mode
*/

#include "server.h"

status_t pasv(client_t *client, char *param)
{
    //create a DATA socket
    //open the DATA socket, with same network interface as server
    //bind a free port
    //if all ok, send [227 ip1:ip2:ip3:ip4 ??? ???] to client from server
    return OK;
}

status_t port(client_t *client, char *param)
{
    return OK;
}
