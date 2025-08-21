#include "server.h"
#include "client.h"
#include "http.h"
#include "socket.h"
#include "io.h"

void handle_client(Client *client)
{
    char *ip = inet_ntoa(client->addr.sin_addr);
    printf("A client connected! %s\n", ip);

    // load in a file
    File *file = read_file("test/index.html");

    // send basic HTTP header with an OK to the client
    HttpResponse *res = response(STATUS_OK, "", file);
    send_res(client, res);
}

int main()
{
    Server *server = init_server(3000, 10);
    printf("Server started on port %d\n", server->port);

    serve(server, &handle_client);
    close_server(server);
}

// parse headers
