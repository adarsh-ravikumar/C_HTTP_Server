#include "utils.h"

char *strstatus(Status status) {
    switch (status) {
        case STATUS_OK:               return "OK";
        case STATUS_MOVED_PERM:       return "Moved Permanently";
        case STATUS_FORBIDDEN:        return "Forbidden";
        case STATUS_NOT_FOUND:        return "Not Found";
        case STATUS_INTERNAL_ERROR:   return "Internal Server Error";
        case STATUS_GATEWAY_ERROR:    return "Bad Gateway";
        case STATUS_UNAVAILABLE:      return "Service Unavailable";
        default:                      return "Unknown Status";
    }
}


void panic(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");

    va_end(args);

    if (errno != 0)
    {
        fprintf(stderr, "errno = %d: %s\n", errno, strerror(errno));
    }

    exit(EXIT_FAILURE);
}