#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/types.h"
#include "../include/dotenv.h"
#include "../include/client.h"
#include "../include/build_url.h"

client_t *new_client(void)
{
    dotenv_t *dotenv = 0;
    // Filename can't have a length higher than 256.
    char dotenv_path[257];
    char *client_id = 0;
    char *client_secret = 0;
    client_t *client = (client_t *)malloc(sizeof(client_t));

    if (!client) {
        perror("Error :");
        return client;
    }
    printf("Where is your .env file ?\n(enter file's path) : ");
    scanf("%s", dotenv_path);
    dotenv = load_env(dotenv_path);
    if (!dotenv) {
        destroy_client(client);
        perror("Error :");
        return client;
    }
    client_id = get_var(dotenv, "CLIENT_ID");
    client_secret = get_var(dotenv, "CLIENT_SECRET");
    if (!client_id || !client_secret) {
        fprintf(stderr, "%s\n", "Neither client_id nor client_secret was found !");
        destroy_client(client);
        destroy_env(dotenv);
        exit(1);
        return client;
    }
    client->client_id = strdup(client_id);
    client->client_secret = strdup(client_secret);
    client->scope = build_oauth2_scopes(1);
    destroy_env(dotenv);
    return client;
}

void destroy_client(client_t *self)
{
    if (!self)
        return;
    if (self->client_id)
        free(self->client_id);
    if (self->client_secret)
        free(self->client_secret);
    if (self->scope)
        free(self->scope);
    free(self);
}
