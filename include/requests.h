#ifndef _TERMCORD_REQUESTS
#define _TERMCORD_REQUESTS
#include "types.h"

request_t *new_request(char const *method, char const *url, char const *body);
response_t *execute_request(request_t *self);
void close_request(request_t *self);
void destroy_response(response_t *self);
request_headers_t *new_headers(void);
request_headers_t *add_header(request_headers_t *self, char *field, char *value);

#endif
