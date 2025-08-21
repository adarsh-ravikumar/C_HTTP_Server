#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <stdarg.h>
#include <errno.h>

#include <string.h>

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;

typedef enum
{
    STATUS_OK = 200,
    STATUS_MOVED_PERM = 301,
    STATUS_FORBIDDEN = 403,
    STATUS_NOT_FOUND = 404,
    STATUS_INTERNAL_ERROR = 500,
    STATUS_GATEWAY_ERROR = 502,
    STATUS_UNAVAILABLE = 503
} Status;

typedef enum
{
    GET,    // get resource
    POST,   // create resource
    PUT,    // overwrite resource
    PATCH,  // update resource
    DELETE, // delete resources
} Action;

char *strstatus(Status status);

void panic(const char *fmt, ...);
