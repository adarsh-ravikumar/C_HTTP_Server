#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include "hashmap.h"
#include "utils.h"

#include <stdbool.h>

typedef struct
{
    size_t size;
    char *name;
    char *content;
    MimeType mime_type;
} File;

typedef struct
{
    Hashmap *map;
    File *not_found;
} Router;

typedef struct
{
    int socket;
    sockaddr_in addr;
} Client;

typedef struct
{
    int port;
    int socket;
    int backlog;
    Router *router;
} Server;

typedef struct
{
    Hashmap *map;
} Headers;

typedef struct
{
    Status status;
    char *version;
    Headers *headers;
    File *body;
    char *response_header;
    size_t response_header_size;
} HttpResponse;

typedef struct
{
    Method method;
    char *version;
    char *path;
    Headers *headers;
    char *body;
} HttpRequest;