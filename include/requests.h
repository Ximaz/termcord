#ifndef _TERMCORD_REQUESTS
#define _TERMCORD_REQUESTS
#include <string.h>
#include <curl/curl.h>

typedef struct response_s
{
    char *memory;
    size_t size;
} response_t;

typedef struct request_header_s
{
    char *field;
    char *value;
} request_header_t;

typedef struct request_headers_s
{
    size_t headers_len;
    request_header_t **headers;
} request_headers_t;

typedef struct request_s
{
    char const *url;
    char const *body;
    char const *method;
    request_headers_t *headers;
} request_t;

request_t *new_request(char const *method, char const *url, char const *body);
response_t *execute_request(request_t *self);
void close_request(request_t *self);
void destroy_response(response_t *self);
request_headers_t *new_headers(void);
request_headers_t *add_header(request_headers_t *self, char *field, char *value);

#endif
