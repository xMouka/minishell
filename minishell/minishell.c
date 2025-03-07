#include "minishell.h"



int main()
{
    char *line;

    while (0x69)
    {
        line = readline("drugs$ ");
        if (!line)
            break;
        printf("%s\n", line);
        free(line);
    }
    return 0;
}