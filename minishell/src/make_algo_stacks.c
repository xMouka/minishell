#include "../minishell.h"

t_stack *make_stacks(t_tokens *tokens)
{
    t_stack *stack_a;
    t_stack *stack_b;

    if (!tokens) {
        return NULL;
    }
    while (tokens)
    {
        if (tokens->type == TOKEN_COMMAND)
        {
        
        }
    }
}