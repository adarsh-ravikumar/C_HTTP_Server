#include "hashmap.h"



// Simple djb2 hash
static unsigned long hash(const char *str)
{
    unsigned long h = 5381;
    int c;
    while ((c = *str++))
    {
        h = ((h << 5) + h) + c;
    }
    return h;
}

Hashmap *init_hashmap(size_t bucket_count)
{
    Hashmap *map = malloc(sizeof(Hashmap));
    if (!map)
        panic("Allocation failed for 'struct Hashmap'");

    map->bucket_count = bucket_count;
    map->buckets = calloc(bucket_count, sizeof(HashmapEntry *));
    if (!map->buckets)
    {
        perror("init_hashmap buckets");
        exit(1);
    }

    return map;
}

void set_hashmap(Hashmap *map, const char *key, void *value)
{
    unsigned long h = hash(key) % map->bucket_count;
    HashmapEntry *curr = map->buckets[h];

    while (curr)
    {
        if (strcmp(curr->key, key) == 0)
        {
            curr->value = value;
            return;
        }
        curr = curr->next;
    }

    HashmapEntry *new = malloc(sizeof(HashmapEntry));
    if (!new)
        panic("Allocation failed for 'HashmapEntry'");

    new->key = strdup(key);
    new->value = value;
    new->next = map->buckets[h];
    map->buckets[h] = new;
}

void *get_hashmap(Hashmap *map, const char *key)
{
    unsigned long h = hash(key) % map->bucket_count;
    HashmapEntry *curr = map->buckets[h];

    while (curr)
    {
        if (strcmp(curr->key, key) == 0)
        {
            return curr->value;
        }
        curr = curr->next;
    }

    return NULL;
}

void free_hashmap(Hashmap *map, void (*free_value)(void *))
{
    for (size_t i = 0; i < map->bucket_count; i++)
    {
        HashmapEntry *curr = map->buckets[i];
        while (curr)
        {
            HashmapEntry *tmp = curr;
            curr = curr->next;

            printf("Freeing key: %s\n", tmp->key);
            free(tmp->key);

            if (free_value){
                printf("Freeing value\n");
                free_value(tmp->value);}

            printf("Freeing tmp\n");
            free(tmp);
        }
    }
    free(map->buckets);
    free(map);
}
