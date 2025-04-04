#include "../minishell.h"
#include <stdio.h>
#include <unistd.h>

int ft_isspace(char c)
{
    if (c == ' ' || c == '\t' || c == '\n')
        return (1);
    return (0);
}
int count_tokens(char *line)
{
    int count;
    char quote;
    int i;

    if (!line)
        return (0);
    count = 0;
    i = 0;
    while (line[i])
    {
        while (line[i] && ft_isspace(line[i]))
            i++;
        if (!line[i])
            break;
        if (ft_strchr("|>&<()\'\"", line[i]))
        {
            if (line[i] == '\'' || line[i] == '\"')
            {
                quote = line[i];
                i++;
                while (line[i] && line[i] != quote)
                    i++;
                if (line[i])
                    i++;
            }
            else if (line[i] == line[i + 1] &&( line[i] == '>' || line[i] == '<'
                    || line[i] == '|' || line[i] == '&'))
                i += 2;
            else
                i++;
            count++;
        }
        else
        {
            while (!ft_strchr("|>&<()", line[i]) && line[i] && !ft_isspace(line[i]))
                i++;
            count++;
        }
    }
    return (count);
}

int count_word(char *line)
{
    int count;

    if (!line)
        return (0);
    count = 0;
    while (!ft_strchr("|><&()", line[count]) && line[count] && !ft_isspace(line[count]))
        count++;
    return (count);
}

void free_tokens(char **tokens, int count)
{
    int i;

    if (!tokens)
        return;
    for (i = 0; i < count; i++)
    {
        if (tokens[i])
            free(tokens[i]);
    }
    free(tokens);
}
char **tokinize(char *line)
{
    char **tokens;
    char quote;
    int word_len;
    int i;
    int j;
    int z;
    
    tokens = malloc((count_tokens(line) + 1)* sizeof(char *));
    if (!tokens)
        return (write(2, "malloc on drugs\n", 17), NULL);
    i = 0;
    j = 0;
    while (line[i])
    {
        while (ft_isspace(line[i]))
            i++;
        if (ft_strchr("\'\"", line[i]))
        {
            word_len = 0;
            quote = line[i];
            i++;
            while (line[i] && line[i] != quote)
            {
                i++;
                word_len++;
            }
            if (!line[i])
            {
                free_tokens(tokens, j);
                return (write(2, "Error: Unterminated quote\n", 26), NULL);
            }
            tokens[j] = malloc((word_len + 3) * sizeof(char));
            if (!tokens[j])
            {
                free_tokens(tokens, j);
                return (write(2, "malloc on drugs\n", 17), NULL);
            }
            tokens[j][0] = quote;
            z = 1;
            i -= word_len;
            while (z <= word_len)
            {
                tokens[j][z] = line[i];
                z++;
                i++;
            }
            tokens[j][z++] = quote;
            tokens[j][z] = '\0';
            j++;
            i++;
        }
        else if (ft_strchr("|>&<()", line[i]))
        {
            if (line[i] == line[i + 1] && line[i] != '(' && line[i] != ')')
            {
                tokens[j] = malloc(3 * sizeof(char));
                if (!tokens[j])
                {
                    free_tokens(tokens, j);
                    return (write(2, "malloc on drugs\n", 17), NULL);
                }
                tokens[j][0] = line[i];
                tokens[j][1] = line[i];
                tokens[j][2] = '\0';
                i += 2;
            }
            else
            {
                tokens[j] = malloc(2 * sizeof(char));
                if (!tokens[j])
                {
                    free_tokens(tokens, j);
                    return (write(2, "malloc on drugs\n", 17), NULL);
                }
                tokens[j][0] = line[i];
                tokens[j][1] = '\0';
                i++;
            }
            j++;
        }
        else
        {
            word_len = count_word(&line[i]);
            tokens[j] = malloc((word_len + 1) * sizeof(char));
            if (!tokens[j])
                return (free_tokens(tokens, j), write(2, "malloc on drugs\n", 17), NULL);
            z = 0;
            while (z < word_len)
                tokens[j][z++] = line[i++];
            tokens[j][z] = '\0';
            j++;
        }
    }
    tokens[j] = NULL;
    return tokens;
}
