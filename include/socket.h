#pragma once

#include "common.h"

void send_res(Client *client, HttpResponse *res);
HttpRequest *recv_req(Client *client);