#ifndef _TERMCORD_CLIENT
#define _TERMCORD_CLIENT
#include "types.h"

client_t *new_client(void);
void destroy_client(client_t *self);

#endif
