/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:33:34 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/12 16:09:13 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "libft.h"

/* Main Shell Struct */
typedef struct s_shell
{
	char	**env;
	int		last_exit_status;
}	t_shell;

/* Tokenizer (Lexer) */
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_REDIR_APPEND,
	TOKEN_LPAREN,
	TOKEN_RPAREN
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

/* Parser (AST) */
typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_AND,
	NODE_OR
}	t_node_type;

typedef struct s_ast_node	t_ast_node;

typedef struct s_redir
{
	char			*filename;
	t_token_type	type;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd_node
{
	char	**argv;
	t_redir	*redirections;
}	t_cmd_node;

typedef struct s_op_node
{
	t_ast_node	*left;
	t_ast_node	*right;
}	t_op_node;

struct s_ast_node
{
	t_node_type	type;
	union
	{
		t_cmd_node	command;
		t_op_node	operator;
	} u_as;
};

typedef struct s_parser
{
	t_token	*current_token;
}	t_parser;

typedef struct s_quote_state
{
	char	quote_char;
	int		i;
	int		j;
}	t_quote_state;

/* Function Prototypes */

/* env.c */
int			init_shell_env(t_shell *shell, char **envp);
void		free_shell_env(t_shell *shell);

/* lexer.c & handle_tokens.c & handle_operator_token.c */
t_token		*main_lexer(const char *line);
int			handle_operator_token(t_token **list, const char *line);
int			handle_word_token(t_token **list, const char *line);
t_token		*create_token(char *value, t_token_type type);
void		add_token_back(t_token **list_head, t_token *new_token);

/* build_ast.c & parse_command.c */
t_ast_node	*build_ast(t_token *tokens);
t_ast_node	*parse_logical_op(t_parser *parser);
t_ast_node	*parse_pipe(t_parser *parser);
t_ast_node	*parse_simple_cmd(t_parser *parser);
int			handle_redirection(t_parser *parser, t_ast_node *node);

/* utils_build_ast.c */
t_ast_node	*create_ast_node(t_node_type type);
t_redir		*create_redir(t_token_type type, char *filename);
void		add_redir_to_node(t_ast_node *node, t_redir *redir);
void		next_token(t_parser *parser);

/* executor.c & execute_command.c & execute_pipe.c */
int			execute_ast(t_shell *shell, t_ast_node *node);
int			execute_command_node(t_shell *shell, t_ast_node *node);
int			execute_pipe_node(t_shell *shell, t_ast_node *node);

/* handle_redirections.c */
int			apply_redirections(t_cmd_node *cmd);

/* path_finder.c */
char		*find_command_path(char *cmd);

/* remove_quotes.c */
char		*remove_quotes(char *str);

/* cleanup.c */
void		free_token_list(t_token *list_head);
void		free_ast(t_ast_node *node);

/* utils.c */
int			is_whitespace(char c);
int			is_operator(char c);

/* debug.c & ast_debugger.c */
void		print_token_list(t_token *list);
void		print_ast(t_ast_node *root);

#endif