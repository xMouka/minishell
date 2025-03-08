#include "../minishell.h"


t_ast_node *create_node(t_ast_type type, char *cmd)
{
    t_ast_node *node;

    node = malloc(sizeof(t_ast_node));
    if (!node)
        return (NULL);
    node->type = type;
    node->left = NULL;
    node->right = NULL;
    if (type == AST_CMD)
    {
        node->args = ft_split(cmd, " ");
        node->redirections = NULL;
    }
    return (node);
}





void build_tree(t_tokens *tokens)
{
    t_tokens *tmp;
    t_ast_node *head;
    t_ast_node *temp;
    
    tmp = tokens;
    temp = head;
    while (tokens)
    {
        if (tokens->type == TOKEN_PAREN_OPEN)
        {
            
        }
    }
}