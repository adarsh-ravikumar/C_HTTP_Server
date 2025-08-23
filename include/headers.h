#pragma once
#include "common.h"

#define HEADER_COUNT 32

Headers *init_header(size_t bucket_count);
void set_header(Headers *map, const char *key, const char *value);
const char *get_header(Headers *map, const char *key);
void free_header(Headers *map);

char *build_headers(Headers *headers);
