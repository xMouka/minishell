#include "../minishell.h"
#include <stdlib.h>


static int ft_is_cmd(char *arg)
{
    if (!ft_strcmp(arg, "||") || !ft_strcmp(arg, "&&") || ft_strcmp(arg, "|") 
    || !ft_strcmp(arg, "<<") || !ft_strcmp(arg, ">>") || !ft_strcmp(arg, "<") 
    || !ft_strcmp(arg, ">") ) {
        return (0);
    }
    return (1);
}
static t_tokens *ft_new_node(char *arg, int type)
{
    t_tokens *node;

    node = malloc(sizeof(t_tokens));
    if (!node)
        return (NULL);
    node->cmd = arg;
    node->type = type;
    node->next = NULL;
    node->redirections = NULL;
    return (node);
}

static void put_redir(t_tokens *token, char *file, t_token_type type)
{
    t_redirection *redir;
    t_redirection *tmp;

    redir = malloc(sizeof(t_redirection));
    if (!redir)
        return ;
    redir->file = file;
    redir->type = type;
    redir->next = NULL;
    if (!token->redirections)
        token->redirections = redir;
    else
    {
        tmp = token->redirections;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = redir;
    }
}

// tokens to linked list to detect format
// join command seprated by space in the same node

t_tokens *tokens_list(char **args)
{
    t_tokens *node;
    t_tokens *head;
    int i;
    char *temp;
    char *cmd;
    

    if (!args)
        return (NULL);
    // << >> < > | || && cmd
    i = 0;
    while(args[i])
    {
        cmd = "";
        while  (ft_is_cmd(args[i]) || ft_strcmp(args[i], "<") || ft_strcmp(args[i], ">")
            || ft_strcmp(args[i], "<<") || ft_strcmp(args[i], ">>"))
        {
            node = ft_new_node(cmd, 0);
            while (ft_is_cmd(args[i]))
            {
                temp = ft_strdup(args[i]);
                cmd = ft_strjoin(temp, " ");
                free(temp);
                i++;
            }
            if (ft_strcmp(args[i], "<"))
                put_redir(node, args[i + 1], TOKEN_REDIR_IN);
            else if (ft_strcmp(args[i], ">"))
                put_redir(node, args[i + 1], TOKEN_REDIR_OUT);
            else if (ft_strcmp(args[i], "<<"))
                put_redir(node, args[i + 1], TOKEN_HEREDOC);
            else if (ft_strcmp(args[i], ">>"))
                put_redir(node, args[i + 1], TOKEN_APPEND);
            i += 2;
        }
        if (ft_strcmp(args[i], "|"))
            node = ft_new_node(args[i], TOKEN_PIPE);
        else if (ft_strcmp(args[i], "||"))
            node = ft_new_node(args[i], TOKEN_OR);
        else if (ft_strcmp(args[i], "&&"))
            node = ft_new_node(args[i], TOKEN_AND);
        else if (ft_strcmp(args[i], "("))
            node = ft_new_node(args[i], TOKEN_PAREN_OPEN);
        else if (ft_strcmp(args[i], ")"))
            node = ft_new_node(args[i], TOKEN_PAREN_CLOSE);
        if (i == 0)
            head = node;
        else if (ft_strcmp(args[i], "|") || ft_strcmp(args[i], "||") 
                || ft_strcmp(args[i], "&&") || ft_strcmp(args[i], "(")
                || ft_strcmp(args[i], ")"))
        {
            head->next = node;
            head = head->next;
        }
        i++;
    }
    return (head);
}