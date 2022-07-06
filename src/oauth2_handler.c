#include <stdlib.h>
#include <string.h>
#include "../include/types.h"
#include "../include/base64.h"
#include "../include/requests.h"
#include "../include/build_url.h"

static char *forge_body(client_t *client)
{
    char *format = "grant_type=client_credentials&scope=%s";
    size_t body_len = strlen(format) + strlen(client->scope);
    char *body = (char *) calloc(body_len + 1, sizeof(char));

    if (!body)
        return body;
    sprintf(body, format, client->scope);
    printf("BODY : %s\n", body);
    body[body_len] = 0;
    return body;
}

static char *forge_bearer_token(client_t *client)
{
    char *clear_token = 0;
    char *bearer_token = 0;
    char *authorization = 0;
    size_t bearer_token_len = strlen(client->client_id) + strlen(client->client_secret) + 1;

    if (!client)
        return authorization;
    clear_token = (char *) calloc(bearer_token_len + 1, sizeof(char));
    if (!clear_token)
        return authorization;
    sprintf(clear_token, "%s:%s", client->client_id, client->client_secret);
    bearer_token = b64_encode(clear_token);
    free(clear_token);
    authorization = (char *) calloc(strlen(bearer_token) + strlen("Basic ") + 1, sizeof(char));
    if (!authorization) {
        free(bearer_token);
        return authorization;
    }
    sprintf(authorization, "Basic %s", bearer_token);
    free(bearer_token);
    return authorization;
}


response_t *get_access_token(client_t *client)
{
    char *body = 0;
    request_t *req = 0;
    response_t *resp = 0;
    char *bearer_token = 0;

    body = forge_body(client);
    if (!body)
        return resp;
    bearer_token = forge_bearer_token(client);
    if (!bearer_token) {
        free(body);
        return resp;
    }
    req = new_request("POST", "https://discord.com/api/oauth2/token", body);
    if (!req) {
        free(bearer_token);
        return resp;
    }
    req->headers = add_header(req->headers, "Content-Type", "application/x-www-form-urlencoded");
    req->headers = add_header(req->headers, "Authorization", bearer_token);
    resp = execute_request(req);
    free(bearer_token);
    free(body);
    close_request(req);
    return resp;
}
