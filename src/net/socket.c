#include "socket.h"
#include "http.h"

void send_res(Client *client, HttpResponse *res)
{
    build_response_header(res);

    int header_send_status = send(client->socket, res->response_header, res->response_header_size, 0);

    if (header_send_status < 0)
    {
        panic(
            "Failed to send response header to client %u @ %s",
            client->socket, inet_ntoa(client->addr.sin_addr));
    }

    int content_send_status = send(client->socket, res->body->content, res->body->size, 0);

    if (content_send_status < 0)
    {
        panic(
            "Failed to send content to client %u @ %s",
            client->socket, inet_ntoa(client->addr.sin_addr));
    }
}

HttpRequest *recv_req(Client *client)
{
    char *req_str = malloc(4096);
    if (!req_str)
        panic("Allocation failed for request string");

    ssize_t n = recv(client->socket, req_str, 4096, 0);
    if (n < 0)
    {
        free(req_str);
        panic("Recieve failed");
    }

    req_str[n] = '\0';

    HttpRequest *req = request(req_str);

    free(req_str);

    return req;
}