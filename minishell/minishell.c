#include "minishell.h"



int main()
{
    char *line;
    char **args;

    while (0x69)
    {
        line = readline("drugs$ ");
        if (!line)
            break;
        args = tokinize(line);
        free(line);
    }
    return 0;
}