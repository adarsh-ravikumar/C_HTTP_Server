#include "server.h"
#include "client.h"
#include "http.h"
#include "socket.h"
#include "headers.h"
#include "io.h"

void handle_client(Router *router, Client *client)
{
    char *ip = inet_ntoa(client->addr.sin_addr);
    printf("A client connected! %s\n", ip);

    HttpRequest *req = recv_req(client);
    HttpResponse *res = resolve_request(router, req);
    send_res(client, res);

    free_request(req);
    free_response(res);
}

void setup_router(Server *server)
{
    File *home = read_file("test/index.html", TEXT_HTML);
    File *about = read_file("test/about.html", TEXT_HTML);
    File *new_route = read_file("test/new_route.html", TEXT_HTML);
    
    File *not_found = read_file("test/404.html", TEXT_HTML);
    
    File *bear = read_file("test/bear.jpg", IMG_JPEG);
    File *duck = read_file("test/duck.jpg", IMG_JPEG);
    File *hello_there = read_file("test/hello-there.gif", IMG_GIF);

    register_route(server->router, "/", home);
    register_route(server->router, "/about", about);
    register_route(server->router, "/new-route", new_route);
    register_route(server->router, "/bear", bear);
    register_route(server->router, "/duck", duck);
    register_route(server->router, "/hello-there", hello_there);

    server->router->not_found = not_found;
}

int main(int argc, char **argv)
{
    int port = 3000;

    if (argc > 1)
        port = atoi(argv[1]);

    Server *server = init_server(port, 10);
    setup_router(server);

    printf("Server started on port  %d\n", server->port);

    serve(server, &handle_client);
    close_server(server);
}