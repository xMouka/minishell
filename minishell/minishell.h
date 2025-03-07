#ifndef MINISHELL_H

#define MINISHELL_H

#include "libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_redirection {
  char    *file;            // Filename (for >, <, etc.)
  int     type;             // Type (REDIR_IN, REDIR_OUT, HEREDOC, etc.)
  struct s_redirection *next;
} t_redirection;


typedef enum e_ast_type {    // AST == Abstract Syntax Tree
  AST_CMD,     // Simple command (`ls -la`)
  AST_PIPE,    // Pipe operator `|`
  AST_AND,     // Logical AND `&&`
  AST_OR,      // Logical OR `||`
  AST_GROUP    // Parentheses `(...)` to group commands
} t_ast_type;


typedef struct s_ast_node {
  t_ast_type      type;
  struct s_ast_node *left;
  struct s_ast_node *right;
  // For AST_CMD:
  char            **args;           // Command arguments (e.g., ["ls", "-la"])
  t_redirection   *redirections;    // List of input/output redirections
} t_ast_node;






#endif