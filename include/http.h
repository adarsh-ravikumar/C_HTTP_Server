#pragma once

#include "common.h"
#include "server.h"
#include "client.h"

#define RESPONSE_PADDING 512

HttpRequest *request(char *req);
HttpResponse *response(const Status status, char *headers, File *body);
char *build_response(HttpResponse *res);