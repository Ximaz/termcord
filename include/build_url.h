#ifndef _TERMCORD_BUILD_URL
#define _TERMCORD_BUILD_URL
#include "types.h"

char *build_oauth2_scopes(int as_body);
char *build_oauth_url(client_t *client, char const *url);

#endif
