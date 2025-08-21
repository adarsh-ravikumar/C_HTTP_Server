#include "http.h"

// HttpRequest *request(char *req);

HttpResponse *response(const Status status, char *headers, File *body)
{
    HttpResponse *res = (HttpResponse *)malloc(sizeof(HttpResponse));
    if (!res)
        panic("Allocation for 'struct HttpResponse' failed");

    res->status = status;
    res->version = "1.1";
    res->headers = headers;
    res->body = body;

    return res;
}

char *build_response(HttpResponse *res)
{
    size_t header_len = res->body->size + strlen(res->headers) + RESPONSE_PADDING;
    char *response = (char *)malloc(sizeof(char) * header_len);
    if (!response)
        panic("Allocation for response failed");

    sprintf(response,
            "HTTP/%s %d %s\r\nContent-Type: text/html\r\nContent-Length: %ld\r\n",
            res->version, res->status, strstatus(res->status), res->body->size);

    strcat(response, res->headers);
    strcat(response, "\r\n");
    strcat(response, res->body->content);

    return response;
}