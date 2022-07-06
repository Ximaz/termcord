#include <stdlib.h>
#include <string.h>
#include "../include/base64.h"

static size_t b64_encoded_size(size_t inlen)
{
	size_t ret = inlen;

	if (inlen % 3 != 0)
		ret += 3 - (inlen % 3);
	ret /= 3;
	ret *= 4;
	return ret;
}

char *b64_encode(char const *in)
{
	char *out = 0;
	size_t i = 0;
	size_t j = 0;
	size_t v = 0;
	size_t elen = 0;
    size_t len = strlen(in);

	if (!in || len == 0)
		return out;
	elen = b64_encoded_size(len);
	out  = (char *) calloc(elen + 1, sizeof(char));
	out[elen] = 0;
	for (; i < len; i += 3, j += 4) {
		v = in[i];
		v = i + 1 < len ? v << 8 | in[i + 1] : v << 8;
		v = i + 2 < len ? v << 8 | in[i + 2] : v << 8;
		out[j]   = b64chars[(v >> 18) & 0x3F];
		out[j + 1] = b64chars[(v >> 12) & 0x3F];
		if (i + 1 < len)
			out[j + 2] = b64chars[(v >> 6) & 0x3F];
		else
			out[j + 2] = '=';
		if (i + 2 < len)
			out[j + 3] = b64chars[v & 0x3F];
		else
			out[j + 3] = '=';
	}
	return out;
}
