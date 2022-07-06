#include <stdio.h>
#include <stdlib.h>
#include "include/types.h"
#include "include/client.h"
#include "include/oauth2_handler.h"

int main(void)
{
    client_t *client = new_client();
    response_t *access_token_resp = 0;

    printf("%s\n", client->scope);
    access_token_resp = get_access_token(client);
    printf("Access token's response : %s\n", access_token_resp->memory);
    destroy_response(access_token_resp);
    destroy_client(client);
    return 0;
}
