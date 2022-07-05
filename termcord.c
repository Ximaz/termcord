#include <stdio.h>
#include <stdlib.h>
#include "include/types.h"
#include "include/client.h"

int main(void)
{
    client_t *client = new_client();
    printf("\nPlease, allow the Discord OAuth2 app to access to your Discord account :\n\n%s\n", client->oauth2_url);
    destroy_client(client);
    return 0;
}
