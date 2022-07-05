#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/dotenv.h"

static char *strip_end_of_line(char *line)
{
    size_t line_len = strlen(line);

    if (line[line_len - 2] == '\r' && line[line_len - 1] == '\n')
        line[line_len - 2] = 0;
    if (line[line_len - 1] == '\n')
        line[line_len - 1] = 0;
    return line;
}

static dotenv_var_t *load_var(char *line)
{
    size_t i = 0;
    dotenv_var_t *dotenv_var = (dotenv_var_t *) malloc(sizeof(dotenv_var_t));

    line = strip_end_of_line(line);
    while (line[i++] != '=');
    dotenv_var->name = strndup(line, i - 1);
    dotenv_var->value = strdup(&line[i + 1]);
    return dotenv_var;
}

dotenv_t *new_env(void)
{
    dotenv_t *dotenv = (dotenv_t *) malloc(sizeof(dotenv_t));

    if (!dotenv) {
        perror("Error :");
        return dotenv;
    }
    dotenv->vars_len = 0;
    dotenv->vars = (dotenv_var_t **) malloc(sizeof(dotenv_var_t *));
    return dotenv;
}

void destroy_env(dotenv_t *dotenv)
{
    dotenv_var_t *dotenv_var = 0;

    if (!dotenv)
        return;
    for (--dotenv->vars_len; dotenv->vars_len >= 0; dotenv->vars_len--) {
        dotenv_var = dotenv->vars[dotenv->vars_len];
        if (dotenv_var) {
            free(dotenv_var->name);
            free(dotenv_var->value);
            free(dotenv_var);
        }
    }
    free(dotenv->vars);
    free(dotenv);
}

dotenv_t *load_env(char const *filename)
{
    char *line = 0;
    size_t line_len = 0;
    FILE *fp = fopen(filename, "r");
    dotenv_t *dotenv = 0;
    dotenv_var_t *dotenv_var = 0;

    if (!fp) {
        perror("Error: ");
        exit(1);
        return 0;
    }
    dotenv = new_env();
    if (!dotenv) {
        fclose(fp);
        exit(1);
        return 0;
    }
    while (getline(&line, &line_len, fp) > 0) {
        line = strip_end_of_line(line);
        dotenv_var = load_var(line);
        dotenv->vars[dotenv->vars_len++] = dotenv_var;
        dotenv->vars = (dotenv_var_t **) realloc(dotenv->vars, dotenv->vars_len * sizeof(dotenv_var_t));
    }
    free(line);
    fclose(fp);
    return dotenv;
}

char *get_var(dotenv_t *dotenv, char *name)
{
    int i = 0;
    char *buffer = 0;
    dotenv_var_t *dotenv_var = 0;

    if (buffer)
        buffer[0] = 0;
    for (; i < dotenv->vars_len; i++) {
        dotenv_var = dotenv->vars[i];
        if (strcmp(dotenv_var->name, name) == 0)
            buffer = dotenv_var->value;
    }
    if (!buffer)
        buffer = (char *) malloc(sizeof(char));
    return buffer;
}
