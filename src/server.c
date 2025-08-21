#include "server.h"

Server *init_server(int port, int backlog)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock == -1)
        panic("Failed to open socket!");

    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = INADDR_ANY;

    int bind_status = bind(sock, (sockaddr *)&server_address, sizeof(server_address));

    if (bind_status == -1)
        panic("Failed to bind socket at port %d", port);

    Server *server = (Server *)malloc(sizeof(Server));
    if (!server)
        panic("Allocation for 'struct Server' failed");
    
    server->port = port;
    server->socket = sock;
    server->backlog = backlog;

    return server;
}

void serve(Server *server, void (*handle_client)(Client *))
{
    listen(server->socket, server->backlog);

    while (1)
    {
        Client *client = init_client(server);
        handle_client(client);
        close_client(client);
    }
}

void close_server(Server *server)
{
    close(server->socket);
    free(server);
}