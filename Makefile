NAME = minishell

SRC =   main.c \
       lexer.c \
       handle_tokens.c \
       handle_operator_token.c \
       utils.c \
       cleanup.c \
       debug.c \
       build_ast.c \
       utils_build_ast.c \
       ast_debugger.c \
       parse_command.c
		
		
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