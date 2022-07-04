#include <stdio.h>
#include <stdlib.h>
#include <types.h>
#include <build_url.h>

int main(void)
{
    char const *local_server = "http://localhost:7563/discord/oauth";
    char const *client_id = "993615435079630848";
    char const *client_secret = "-";
    char *oauth_url = 0;
    client_t *client = (client_t *)malloc(sizeof(client_t));

    if (!client)
        return 1;
    client->client_id = client_id;
    client->client_secret = client_secret;
    oauth_url = build_oauth_url(client, local_server);
    printf("%s\n", oauth_url);
    free(oauth_url);
    free(client);
    return 0;
}
