#ifndef _TERMCORD_PARSER
#define _TERMCORD_PARSER

typedef struct dotenv_var_s
{
    char *name;
    char *value;
} dotenv_var_t;

typedef struct dotenv_s
{
    int vars_len;
    dotenv_var_t **vars;
} dotenv_t;

dotenv_t *load_env(char const *filename);
char *get_var(dotenv_t *dotenv, char *name);
void destroy_env(dotenv_t *dotenv);

#endif
