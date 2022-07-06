#ifndef _TERMCORD_PARSER
#define _TERMCORD_PARSER
#include "types.h"

dotenv_t *load_env(char const *filename);
char *get_var(dotenv_t *dotenv, char *name);
void destroy_env(dotenv_t *dotenv);

#endif
