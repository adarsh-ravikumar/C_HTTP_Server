#pragma once

#include "common.h"
#include "client.h"
#include "router.h"

Server *init_server(int port, int backglog); // returns socket descriptor 
void serve(Server *server, void (*handle_client)(Router *, Client *));
void close_server(Server *server);