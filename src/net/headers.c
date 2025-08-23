#include "headers.h"
#include <stdlib.h>
#include <string.h>

Headers *init_header(size_t bucket_count)
{
    Headers *hmap = malloc(sizeof(Headers));
    if (!hmap)
        panic("Allocation of 'struct Headers' failed");

    hmap->map = init_hashmap(bucket_count);
    return hmap;
}

void set_header(Headers *map, const char *key, const char *value)
{
    set_hashmap(map->map, key, strdup(value));
}

const char *get_header(Headers *map, const char *key)
{
    return (const char *)get_hashmap(map->map, key);
}

static void free_value(void *val)
{
    free(val);
}

void free_header(Headers *map)
{
    free_hashmap(map->map, free_value);
    free(map);
}


char *build_headers(Headers *headers)
{
    size_t total_len = 0;
    for (size_t i = 0; i < HEADER_COUNT; i++)
    {
        HashmapEntry *entry = headers->map->buckets[i];
        if (!entry) break;

        while (entry != NULL)
        {
            total_len += strlen(entry->key) + 2 + strlen(entry->value) + 2;
            entry = entry->next;
        }
    }
    
    char *res = malloc(total_len + 1);
    if (!res)
        panic("Allocation for result failed");
    
    res[0] = '\0';

    for (size_t i = 0; i < HEADER_COUNT; i++)
    {
        HashmapEntry *entry = headers->map->buckets[i];

        while (entry != NULL)
        {
            strcat(res, entry->key);
            strcat(res, ": ");
            strcat(res, entry->value);
            strcat(res, "\r\n");
            entry = entry->next;
        }
    }

    return res;
}
