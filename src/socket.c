#include "socket.h"
#include "http.h"

void send_res(Client *client, HttpResponse *res)
{
    char *response = build_response(res);
    int send_status = send(client->socket, response, strlen(response), 0);

    if (send_status < 0)
    {
        panic(
            "Failed to send response to client %u @ %s",
            client->socket, inet_ntoa(client->addr.sin_addr));
    }
}