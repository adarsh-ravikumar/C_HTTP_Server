#include "common.h"

#define ROUTES_COUNT 128

// new route
Router *init_router();
void register_route(Router *router, const char *route, File *file);
File *resolve_route(Router *router, const char *route);
