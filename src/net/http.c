#include "http.h"
#include "headers.h"
#include "router.h"

HttpRequest *request(char *request_str)
{
    char *request_cpy = strdup(request_str);
    HttpRequest *req = malloc(sizeof(HttpRequest));
    if (!req)
        panic("Allocation failed for 'struct HttpRequest'");

    char *method = strtok(request_cpy, " ");
    if (strcmp(method, "GET") == 0)
        req->method = METHOD_GET;
    else if (strcmp(method, "POST") == 0)
        req->method = METHOD_POST;
    else if (strcmp(method, "PUT") == 0)
        req->method = METHOD_PUT;
    else if (strcmp(method, "PATCH") == 0)
        req->method = METHOD_PATCH;
    else if (strcmp(method, "DELETE") == 0)
        req->method = METHOD_DELETE;

    char *path = strtok(NULL, " ");
    req->path = strdup(path);

    char *version = strtok(NULL, "\r\n");
    req->version = strdup(version);

    Headers *headers = init_header(HEADER_COUNT);

    char *header_line = strtok(NULL, "\r\n");
    while (header_line != NULL && strlen(header_line) > 0)
    {
        char *colon = strchr(header_line, ':');
        if (!colon)
        {
            header_line = strtok(NULL, "\r\n");
            continue;
        }

        *colon = '\0';
        char *key = header_line;
        char *value = colon + 1;

        size_t len = strlen(value);
        if (len > 0 && value[len - 1] == '\r')
            value[len - 1] = '\0';

        while (*value == ' ')
            value++;

        set_header(headers, key, value);

        header_line = strtok(NULL, "\r\n");
    }

    req->headers = headers;

    char *body_start = strstr(request_str, "\r\n\r\n");
    if (body_start)
        body_start += 4;
    else
        body_start = NULL;

    const char *cl_str = get_header(req->headers, "Content-Length");
    size_t body_len = cl_str ? strtoul(cl_str, NULL, 10) : 0;

    if (body_len > 0 && body_start != NULL)
    {
        req->body = malloc(body_len + 1);
        if (!req->body)
            panic("Allocation failed for request body");

        memcpy(req->body, body_start, body_len);
        req->body[body_len] = '\0';
    }
    else
    {
        req->body = NULL;
    }

    return req;
}

void free_request(HttpRequest *request)
{
    free_header(request->headers);
    free(request);
}

HttpResponse *response(const Status status, Headers *headers, File *body)
{
    HttpResponse *res = malloc(sizeof(HttpResponse));
    if (!res)
        panic("Allocation for 'struct HttpResponse' failed");

    res->status = status;
    res->version = "1.1";
    res->headers = headers;
    res->body = body;

    return res;
}

HttpResponse *resolve_request(Router *router, HttpRequest *request)
{
    File *res = NULL;
    Status status = STATUS_OK;
    MimeType mime_type = UNKNOWN_MIME;

    if (request->method == METHOD_GET)
    {
        res = (File *)get_hashmap(router->map, request->path);

        if (res == NULL)
        {
            res = router->not_found;
            status = STATUS_NOT_FOUND;
        }

        mime_type = get_mime_type(res->name);
    }

    Headers *header_map = init_header(HEADER_COUNT);
    set_header(header_map, "Content-Type", mime_to_str(mime_type));

    char content_length[32];
    sprintf(content_length, "%ld", res->size);
    set_header(header_map, "Content-Length", content_length);

    return response(status, header_map, res);
}

void free_response(HttpResponse *response)
{
    free_header(response->headers);
    free(response->response_header);
    free(response);
}

HttpResponse *build_response_header(HttpResponse *res)
{
    char *headers_str = build_headers(res->headers);

    size_t response_length = strlen(headers_str) + RESPONSE_PADDING;

    char *response_headers = malloc(response_length);
    if (!response_headers)
        panic("Allocation for response failed");

    snprintf(response_headers,
             response_length,
             "HTTP/%s %d %s\r\n"
             "%s"
             "\r\n",
             res->version,
             res->status, status_to_str(res->status), headers_str);

    response_length = strlen(response_headers);
    response_headers[response_length] = '\0';

    res->response_header = response_headers;
    res->response_header_size = response_length;
    
    return res;
}