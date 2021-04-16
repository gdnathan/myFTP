/*
** EPITECH PROJECT, 2021
** ftp
** File description:
** client
*/

#include "server.h"
#include <unistd.h>

void new_client(int socket, client_t **head, network_t *server)
{
    client_t *new = malloc(sizeof(client_t));
    new->auth = false;
    new->controlSocket = socket;
    new->dataSocket = -1;
    new->path = strdup(server->path);
    if (!*head) {
        new->next = new;
        new->prev = new;
        *head = new;
    } else {
        new->next = *head;
        new->prev = (*head)->prev;
        (*head)->prev->next = new;
        (*head)->prev = new;
    }
}

void delete_client(int socket, client_t **head)
{
    close(socket);
    client_t *tmp = *head;
    do {
        tmp = tmp->next;
        if (tmp == *head)
            break;
    } while (tmp->controlSocket != socket);
    tmp->prev->next = tmp->next;
    tmp->next->prev = tmp->prev;
    free(tmp->path);
    if (tmp->username)
        free(tmp->username);
    if (tmp->password)
        free(tmp->password);
    free(tmp);
    if (tmp == *head)
        *head = tmp->next;
}

client_t *find_client(int socket, client_t **head)
{
    client_t *tmp = *head;
    do {
        tmp = tmp->next;
        if (tmp == *head)
            break;
    } while (tmp->controlSocket != socket);
    return tmp;
}
