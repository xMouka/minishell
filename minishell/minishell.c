#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

void print_ast(t_ast_node *node, int depth)
{
    int i;
    
    if (!node)
        return;
    for (i = 0; i < depth; i++)
        printf("  ");
    if (node->type == AST_CMD)
        printf("CMD: %s\n", node->args[0]);
    else if (node->type == AST_PIPE)
        printf("PIPE\n");
    else if (node->type == AST_AND)
        printf("AND\n");
    else if (node->type == AST_OR)
        printf("OR\n");
    
    // Print children
    if (node->left)
        print_ast(node->left, depth + 1);
    if (node->right)
        print_ast(node->right, depth + 1);
}

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
        print_ast(ast, 5);
    }
    return 0;
}