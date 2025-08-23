#pragma once

#include "common.h"
#include "server.h"
#include "client.h"

#define RESPONSE_PADDING 128

HttpRequest *request(char *req);
HttpResponse *resolve_request(Router *router, HttpRequest *request);
void free_request(HttpRequest *request);

HttpResponse *response(const Status status, Headers *header, File *body);
void free_response(HttpResponse *response);

HttpResponse *build_response_header(HttpResponse *res);