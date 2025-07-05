/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:33:34 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/04 17:50:14 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
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
	char	**args;
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

int			is_whitespace(char c);
int			is_operator(char c);
t_token		*create_token(char *value, t_token_type type);
void		add_token_back(t_token **list_head, t_token *new_token);
int			handle_operator_token(t_token **list, const char *line);
int			handle_word_token(t_token **list, const char *line);
t_token		*main_lexer(const char *line);
void		free_token_list(t_token *list_head);
void		print_token_list(t_token *list);

#endif