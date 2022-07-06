#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/types.h"

static int const OAUTH2_SCOPES_LEN = 11;

static char const *OAUTH2_SCOPES[] = {
    "identify",
    "email",
    "connections",
    "guilds",
    "guilds.members.read",
    "gdm.join",
    // REQUIRE DISCORD APPROVAL : "rpc",
    // REQUIRE DISCORD APPROVAL : "rpc.notifications.read",
    // REQUIRE DISCORD APPROVAL : "rpc.voice.read",
    // REQUIRE DISCORD APPROVAL : "rpc.voice.write",
    // REQUIRE DISCORD APPROVAL : "rpc.activities.write",
    // USELESS : "webhook.incoming",
    "messages.read",
    // REQUIRE DISCORD APPROVAL : "applications.builds.upload",
    "applications.builds.read",
    "applications.commands",
    "applications.store.update",
    "applications.entitlements",
    // REQUIRE DISCORD APPROVAL : "activities.read",
    // REQUIRE DISCORD APPROVAL : "activities.write",
    // REQUIRE DISCORD APPROVAL : "relationships.read",
    // REQUIRE DISCORD APPROVAL : "voice",
    // REQUIRE DISCORD APPROVAL : "dm_channels.read",
};

char *build_oauth2_scopes(int as_body)
{
    int i = 0;
    size_t total_len = 0;
    size_t scope_len = 0;
    char const *scope = 0;
    char *separator = as_body ? "+" : "%20";
    size_t separator_len = as_body ? 1 : 3;
    int include_separator = 0;
    char *format = (char *) malloc(sizeof(char));

    if (!format)
        return format;
    format[0] = 0;
    for (; i < OAUTH2_SCOPES_LEN; i++) {
        include_separator = i < OAUTH2_SCOPES_LEN - 1 ? separator_len : 0;
        scope = OAUTH2_SCOPES[i];
        scope_len = strlen(scope);
        total_len += scope_len + include_separator;
        format = (char *) realloc(format, (total_len + 1) * sizeof(char));
        if (!format)
            break;
        format = strncat(format, scope, scope_len);
        if (include_separator)
            format = strncat(format, separator, include_separator);
    }
    format[total_len] = 0;
    return format;
}

char* urlencode(char const *url)
{
    int pos = 0;
    size_t i = 0;
    size_t url_len = strlen(url);
    const char *hex = "0123456789abcdef";
    char *encoded_url = (char *) calloc(strlen(url) * 3 + 1, sizeof(char));

    for (; i < url_len; i++) {
        if (isalnum(url[i])) {
            encoded_url[pos++] = url[i];
        } else {
            encoded_url[pos++] = '%';
            encoded_url[pos++] = hex[url[i] >> 4];
            encoded_url[pos++] = hex[url[i] & 15];
        }
    }
    encoded_url[pos] = 0;
    return encoded_url;
}

char *build_oauth_url(client_t *client, char const *url)
{
    char *format = "https://discord.com/api/oauth2/authorize?client_id=%s&redirect_uri=%s&response_type=code&scope=%s";
    char *scopes = build_oauth2_scopes(0);
    char *url_encoded = urlencode(url);
    size_t buff_len = strlen(format) + strlen(client->client_id) + strlen(url_encoded) + strlen(scopes);
    char *buffer = (char *) calloc(buff_len + 1, sizeof(char));

    sprintf(buffer, format, client->client_id, url_encoded, scopes);
    free(scopes);
    free(url_encoded);
    return buffer;
}
