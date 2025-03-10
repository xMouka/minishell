#include "../minishell.h"
#include <stdio.h>
#include <stdlib.h>


static int ft_is_cmd(char *arg)
{
    if (!ft_strcmp(arg, "||") || !ft_strcmp(arg, "&&") || !ft_strcmp(arg, "|") 
    || !ft_strcmp(arg, "<<") || !ft_strcmp(arg, ">>") || !ft_strcmp(arg, "<") 
    || !ft_strcmp(arg, ">") || !ft_strcmp(arg, "(") || !ft_strcmp(arg, ")")) {
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
    t_tokens *head = NULL;
    t_tokens *current = NULL;
    t_tokens *new_node = NULL;
    char *cmd_str = NULL;
    int i = 0;
    
    if (!args)
        return (NULL);
        
    while (args[i])
    {
        // Handle redirections at beginning or after special tokens
        if (args[i] && (!ft_strcmp(args[i], "<") || !ft_strcmp(args[i], ">") ||
               !ft_strcmp(args[i], "<<") || !ft_strcmp(args[i], ">>")))
        {
            // Create an empty command node if needed
            if (!new_node)
                new_node = ft_new_node(ft_strdup(""), TOKEN_COMMAND);
            // Process redirections
            if (!ft_strcmp(args[i], "<"))
            {
                if (args[i+1])
                    put_redir(new_node, args[i+1], TOKEN_REDIR_IN);
            }
            else if (!ft_strcmp(args[i], ">"))
            {
                if (args[i+1])
                    put_redir(new_node, args[i+1], TOKEN_REDIR_OUT);
            }
            else if (!ft_strcmp(args[i], "<<"))
            {
                if (args[i+1])
                    put_redir(new_node, args[i+1], TOKEN_HEREDOC);
            }
            else if (!ft_strcmp(args[i], ">>"))
            {
                if (args[i+1])
                    put_redir(new_node, args[i+1], TOKEN_APPEND);
            }
            
            i += 2; // Skip redirection token and its argument
        }
        // Handle regular commands
        else if (args[i] && ft_is_cmd(args[i]))
        {
            // Build command string
            if (!new_node)
            {
                cmd_str = ft_strdup("");
                new_node = ft_new_node(cmd_str, TOKEN_COMMAND);
            }
            
            while (args[i] && ft_is_cmd(args[i]))
            {
                char *temp = new_node->cmd;
                if (ft_strlen(new_node->cmd) > 0)
                    new_node->cmd = ft_strjoin(temp, " ");
                else
                    new_node->cmd = ft_strdup("");
                free(temp);
                temp = new_node->cmd;
                new_node->cmd = ft_strjoin(temp, args[i]);
                free(temp);
                i++;
            }
        }
        // Handle special tokens (|, ||, &&, (, ))
        else if (args[i])
        {
            // Add the current command node to our list if it exists
            if (new_node)
            {
                if (!head)
                {
                    head = new_node;
                    current = head;
                }
                else
                {
                    current->next = new_node;
                    current = current->next;
                }
                new_node = NULL;
            }
            // Create node for special token
            if (!ft_strcmp(args[i], "|"))
                new_node = ft_new_node(ft_strdup(args[i]), TOKEN_PIPE);
            else if (!ft_strcmp(args[i], "||"))
                new_node = ft_new_node(ft_strdup(args[i]), TOKEN_OR);
            else if (!ft_strcmp(args[i], "&&"))
                new_node = ft_new_node(ft_strdup(args[i]), TOKEN_AND);
            else if (!ft_strcmp(args[i], "("))
                new_node = ft_new_node(ft_strdup(args[i]), TOKEN_PAREN_OPEN);
            else if (!ft_strcmp(args[i], ")"))
                new_node = ft_new_node(ft_strdup(args[i]), TOKEN_PAREN_CLOSE);
            // Add special token to list
            if (new_node)
            {
                if (!head)
                {
                    head = new_node;
                    current = head;
                }
                else
                {
                    current->next = new_node;
                    current = current->next;
                }
                new_node = NULL;
            }
            
            i++; // Move to next token
        }
        else
            i++; // Skip unrecognized tokens
        
        // If we've processed all args and still have a pending node
        if (!args[i] && new_node)
        {
            if (!head)
            {
                head = new_node;
                current = head;
            }
            else
            {
                current->next = new_node;
                current = current->next;
            }
            new_node = NULL;
        }
    }
    return head;
}
