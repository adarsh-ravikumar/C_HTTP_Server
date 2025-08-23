#include "client.h"

Client *init_client(Server *server)
{
    sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    int client_socket = accept(server->socket, (sockaddr *)&client_addr, &client_len);

    Client *client = malloc(sizeof(Client));
    if (!client)
        panic("Allocation for 'struct Client' failed");

    client->socket = client_socket;
    client->addr = client_addr;

    return client;
}

void close_client(Client *client)
{
    close(client->socket);
    free(client);
}