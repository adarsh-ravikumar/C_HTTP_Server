#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include "utils.h"

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
} Server;

typedef struct
{
    size_t size;
    char *content;
} File;

typedef struct
{
    Status status;
    char *version;
    char *headers;
    File *body;
} HttpResponse;

typedef struct
{
    Action action;
    char *version;
    char *path;
    char *headers;
    char *body;
} HttpRequest;
