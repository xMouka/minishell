#include "minishell.h"
#include <stdio.h>
#include <unistd.h>



int main()
{
    char *line;
    char **args;
    t_stack *stack;
    t_tokens *tokens;
    t_ast_node *ast;

    while (0x69)
    {
        line = readline("drugs$ ");
        if (!line)
            break;
        args = tokinize(line);
        tokens = tokens_list(args);
        stack = shuntin_yard(tokens);
        ast = make_tree(stack);
        while (ast)
        {
            printf("type: %d\n", ast->type);
            ast = ast->left;
        }
    }
    return 0;
}