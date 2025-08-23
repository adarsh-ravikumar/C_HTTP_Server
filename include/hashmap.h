#pragma once

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include "utils.h"

typedef struct HashmapEntry {
    char *key;
    void *value;
    struct HashmapEntry *next;
} HashmapEntry;

typedef struct {
    HashmapEntry **buckets;
    size_t bucket_count;
} Hashmap;

Hashmap *init_hashmap(size_t bucket_count);
void set_hashmap(Hashmap *map, const char *key, void *value);
void *get_hashmap(Hashmap *map, const char *key);
void free_hashmap(Hashmap *map, void (*free_value)(void *));
