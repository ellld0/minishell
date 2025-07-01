/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:33:34 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/01 10:54:40 by sdavi-al         ###   ########.fr       */
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
t_command	*parser(t_token *tokens);
void		executor(t_command *cmd);
char		*find_command_path(char *cmd);
int			do_pwd(void);
int			do_echo(char **args);
int			apply_redirections(t_command *cmd);
int			do_cd(char **args);
void		do_exit(char **args);
void		do_env(void);
void		do_export(char **args);
int			is_builtin(char *cmd_name);
void		execute_builtin(t_command *cmd);
void		execute_single_command(t_command *cmd, char **envp);
int			dispatch_builtin(t_command *cmd);
void		setup_child_io(t_command *cmd, int *pipe_fds, int prev_read_end);
void		execute_and_exit(t_command *cmd);
void		run_command_in_child(t_command *cmd, int *pipe_fds,
				int prev_read_end);
void		parent_pipe_handler(int *pipe_fds, int *prev_read_end,
				t_command *cmd);
void		wait_for_children(int last_pid);
t_list		**get_env_list(void);
void		init_env(char **envp);
char		**env_list_to_array(void);
void		free_array(char **env_arr);
void		free_env(void);
char		*get_env_value(const char *name);
t_list		*find_env_node(const char *name);
void		set_env_var(const char *name, const char *value);
void		do_unset(char **args);
char		*heredoc_reader(const char *delimiter);
void		handle_file_redirection(t_command *cmd, t_token *redir_token);
t_command	*process_segment(t_token **token_ptr);
void		handle_heredoc(t_command *cmd, t_token *heredoc_token);
#endif