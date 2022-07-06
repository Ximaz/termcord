#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>
#include "../include/requests.h"

static size_t store_response(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    response_t *mem = (response_t *)userp;
    char *ptr = (char *) realloc(mem->memory, (mem->size + realsize + 1) * sizeof(char));
    if (!ptr) {
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }
    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
    return realsize;
}

static struct curl_slist *build_headers(request_headers_t *self)
{
    size_t i = 0;
    char *buf = 0;
    size_t buf_len = 0;
    struct curl_slist *list = 0;
    request_header_t *header = 0;

    if (self->headers_len == 0)
        return list;
    for (; i < self->headers_len; i++) {
        header = self->headers[i];
        if (header) {
            buf_len = strlen(header->field) + strlen(header->value) + 2;
            buf = (char *) calloc(buf_len + 1, sizeof(char));
            sprintf(buf, "%s: %s", header->field, header->value);
            buf[buf_len] = 0;
            list = curl_slist_append(list, buf);
            free(buf);
        }
    }
    return list;
}

// Function about headers themselves.

request_headers_t *new_headers(void)
{
    request_headers_t *headers = (request_headers_t *) malloc(sizeof(request_headers_t));

    if (!headers)
        return headers;
    headers->headers_len = 0;
    headers->headers = (request_header_t **) malloc(sizeof(request_header_t *));
    return headers;
}

static request_header_t *new_header(char *field, char *value)
{
    request_header_t *header = 0;

    if (!field || !value)
        return header;
    header = (request_header_t *) malloc(sizeof(request_header_t));
    if (header) {
        header->field = field;
        header->value = value;
    }
    return header;
}

request_headers_t *add_header(request_headers_t *self, char *field, char *value)
{
    if (!field || !value)
        return self;
    self->headers[self->headers_len++] = new_header(field, value);
    self->headers = (request_header_t **) realloc(self->headers, (self->headers_len + 1) * sizeof(request_header_t *));
    return self;
}

static void destroy_headers(request_headers_t *self)
{
    size_t i = 0;

    if (!self)
        return;
    for (; i < self->headers_len; i++)
        free(self->headers[i]);
    free(self->headers);
    free(self);
}

// Functions about request itself.

request_t *new_request(char const *method, char const *url, char const *body)
{
    request_t *request = 0;

    request = (request_t *) malloc(sizeof(request_t));
    if (!request)
        return request;
    request->url = url;
    request->method = method;
    request->body = body;
    request->headers = new_headers();
    return request;
}

response_t *execute_request(request_t *self)
{
    CURL *curl = 0;
    CURLcode res = 200;
    struct curl_slist *list = 0;
    response_t *response = 0;

    response = (response_t *) malloc(sizeof(response_t));
    if (!response)
        return response;
    response->memory = (char *) calloc(1, sizeof(char));
    if (!response->memory) {
        destroy_response(response);
        return response;
    }
    response->size = 0;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, self->url);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)response);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, store_response);
        if (self->body)
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, self->body);
        if (self->headers) {
            list = build_headers(self->headers);
            if (list)
                curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
        }
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        curl_slist_free_all(list);
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return response;
}

void close_request(request_t *self)
{
    if (!self)
        return;
    destroy_headers(self->headers);
    free(self);
}

// Functions about response itself.

void destroy_response(response_t *self)
{
    if (!self)
        return;
    if (self->memory)
        free(self->memory);
    free(self);
}
