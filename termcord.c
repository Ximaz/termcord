#include <stdio.h>
#include <stdlib.h>
#include "include/types.h"
#include "include/dotenv.h"
#include "include/build_url.h"

int main(void)
{
    char const *local_server = "http://localhost:7563/discord/oauth";
    // char const *client_id = "993615435079630848";
    // char const *client_secret = "-";
    dotenv_t *dotenv = 0;
    char *oauth_url = 0;
    client_t *client = (client_t *)malloc(sizeof(client_t));

    if (!client) {
        perror("Error :");
        return 1;
    }
    dotenv = load_env(".env");
    if (!dotenv) {
        free(client);
        perror("Error :");
        return 1;
    }
    client->client_id = get_var(dotenv, "CLIENT_ID");
    client->client_secret = get_var(dotenv, "CLIENT_SECRET");
    oauth_url = build_oauth_url(client, local_server);
    printf("%s\n", oauth_url);
    destroy_env(dotenv);
    free(oauth_url);
    free(client);
    return 0;
}
