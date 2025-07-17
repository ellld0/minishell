NAME = minishell

SRC =   ast_debugger.c \
        build_ast.c \
        cleanup.c \
        debug.c \
        env.c \
        env_expansion.c \
        env_utils.c \
        execute_pipe.c \
        executor.c \
        handle_operator_token.c \
        handle_redirections.c \
        handle_tokens.c \
        lexer.c \
        main.c \
        parse_command.c \
        path_finder.c \
        remove_quotes.c \
        signals.c \
        utils.c \
        utils_build_ast.c \
        wildcard.c \
        wildcard_expansion.c  \
        builtins.c \
        builtin_dispatcher.c \
        env_management.c \
        builtins2.c \
        syntax_error.c \
        parse_parentheses.c \
        heredoc.c \
        expansion.c
		
LIBFT_DIR = ./libft

LIBFT_LIB = $(LIBFT_DIR)/libft.a				

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -I $(LIBFT_DIR) 

LIBS = -L$(LIBFT_DIR) -lft -lreadline

all: $(NAME)

$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT_LIB)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
