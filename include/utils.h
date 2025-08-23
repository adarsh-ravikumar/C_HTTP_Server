#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <stdarg.h>
#include <errno.h>

#include <string.h>
#include <stdbool.h>

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
    METHOD_GET,    // get resource
    METHOD_POST,   // create resource
    METHOD_PUT,    // overwrite resource
    METHOD_PATCH,  // update resource
    METHOD_DELETE, // delete resources
} Method;

typedef enum
{
    TEXT_HTML,
    TEXT_CSS,
    TEXT_PLAIN,
    APP_JSON,
    APP_JS,
    IMG_PNG,
    IMG_JPEG,
    IMG_GIF,
    IMG_SVG,
    AUDIO_MPEG,
    VIDEO_MP4,
    UNKNOWN_MIME
} MimeType;

char *status_to_str(Status status);

const char *mime_to_str(MimeType mime_type);

MimeType get_mime_type(char *filename);

char *get_file_extension(char *filename);

MimeType mime_from_string(char *mime_str);

bool is_text_file(MimeType mime_type);

void panic(const char *fmt, ...);
