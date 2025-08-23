#include "utils.h"

char *status_to_str(Status status)
{
    switch (status)
    {
    case STATUS_OK:
        return "OK";
    case STATUS_MOVED_PERM:
        return "Moved Permanently";
    case STATUS_FORBIDDEN:
        return "Forbidden";
    case STATUS_NOT_FOUND:
        return "Not Found";
    case STATUS_INTERNAL_ERROR:
        return "Internal Server Error";
    case STATUS_GATEWAY_ERROR:
        return "Bad Gateway";
    case STATUS_UNAVAILABLE:
        return "Service Unavailable";
    default:
        return "Unknown Status";
    }
}
