#ifndef _TERMCORD_TYPES
#define _TERMCORD_TYPES

// Types about client :

typedef struct client_s
{
    char *client_id;
    char *client_secret;
    char *scope;
} client_t;

// Types about dotenv :

typedef struct dotenv_var_s
{
    char *name;
    char *value;
} dotenv_var_t;

typedef struct dotenv_s
{
    int vars_len;
    dotenv_var_t **vars;
} dotenv_t;

// Types about requests :
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

#endif
