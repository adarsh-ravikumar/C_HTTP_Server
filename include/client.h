#pragma once

#include "common.h"

Client *init_client(Server *server);
void close_client(Client *client);