#pragma once

#include "common.h"
#include "client.h"


Server *init_server(int port, int backglog); // returns socket descriptor 
void serve(Server *server, void (*handle_client)(Client *));
void close_server(Server *server);