#include "router.h"

Router *init_router()
{
    Router *router = malloc(sizeof(Router));
    Hashmap *map = init_hashmap(ROUTES_COUNT);
    router->map = map;

    return router;
}

void register_route(Router *router, const char *path, File *file)
{
    set_hashmap(router->map, path, file);
}
