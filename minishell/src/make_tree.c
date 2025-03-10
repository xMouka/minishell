#include "../minishell.h"






t_ast_node *make_tree(t_stack *stack)
{
    t_ast_node *tree_stack;
    t_ast_node *temp;
    t_op_node *op_node;


    while (stack)
    {
        if (stack->token->type == TOKEN_COMMAND)
        {
            
        }
    }
}