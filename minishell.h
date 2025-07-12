/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:33:34 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/10 14:47:14 by sdavi-al         ###   ########.fr       */
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

int			is_whitespace(char c);
int			is_operator(char c);
t_token		*create_token(char *value, t_token_type type);
void		add_token_back(t_token **list_head, t_token *new_token);
int			handle_operator_token(t_token **list, const char *line);
int			handle_word_token(t_token **list, const char *line);
t_token		*main_lexer(const char *line);
void		free_token_list(t_token *list_head);
void		free_ast(t_ast_node *node);
void		print_token_list(t_token *list);
t_ast_node	*create_ast_node(t_node_type type);
t_redir		*create_redir(t_token_type type, char *filename);
void		add_redir_to_node(t_ast_node *node, t_redir *redir);
void		next_token(t_parser *parser);
t_ast_node	*parse_logical_op(t_parser *parser);
t_ast_node	*parse_pipe(t_parser *parser);
t_ast_node	*parse_simple_cmd(t_parser *parser);
t_ast_node	*build_ast(t_token *tokens);
void		print_ast(t_ast_node *root);
int			handle_redirection(t_parser *parser, t_ast_node *node);
void		populate_argv(t_ast_node *node, char **argv_list, int argc);
char		*remove_quotes(char *str);
int			execute_ast(t_ast_node *node);
char		*find_command_path(char *cmd);
int			apply_redirections(t_cmd_node *cmd);

#endif