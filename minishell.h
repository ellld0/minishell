/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:33:34 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/06/25 18:05:00 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	char			*filename;
	t_token_type	type;
	struct s_redir	*next;
}	t_redir;

typedef struct s_command
{
	char				**args;
	t_redir				*redirections;
	struct s_command	*next;
}	t_command;

void		add_token_back(t_token **list, t_token *new_node);
int			append_token(t_token **list, const char *line, int len,
				t_token_type type);
int			handle_operator_token(t_token **token_list, const char *line);
t_token		*main_lexer(char *line);
int			is_whitespace(char c);
int			is_operator(char c);
int			handle_word_token(t_token **token_list, const char *line);
void		free_token_list(t_token *list);
void		free_command_table(t_command *cmd_head);
void		print_command_table(t_command *cmd_head);
void		print_token_list(t_token *list);
char		*remove_quotes(const char *str);
void		redir_add_back(t_redir **list, t_redir *new_redir);
void		handle_redirection(t_command *cmd, t_token **token_ptr);
t_command	*parser(t_token *tokens);

#endif