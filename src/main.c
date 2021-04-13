/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** main
*/

#include "server.h"

status_t ftp_server(network_t *);

status_t parse_input(int ac, char **av, network_t *infos)
{
    if ((ac == 2 && (strcmp(av[1], "--help") || strcmp(av[1], "-h"))) || ac != 3) {
        printf("USAGE: ./myftp port path\n");
        printf("\tport  is the port number on which the server socket listen");
        printf(
            "\tpath  is the path to the home directory for the Anonymous user");
        return ac == 2 ? EXIT : ERROR;
    }
    if (av[1][0] >= '0' && av[1][0] <= '9')
        infos->port = atoi(av[1]);
    else
        return ERROR;
    infos->path = strdup(av[2]);
    return OK;
}

int main(int ac, char **av)
{
    network_t serv_info;
    status_t s;

    s = parse_input(ac, av, &serv_info);
    if (s != OK) {
        return s;
    }
    return ftp_server(&serv_info);
}
