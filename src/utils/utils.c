#include "utils.h"

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