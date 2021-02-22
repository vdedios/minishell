NAME=minishell

CC=gcc
RM = rm -rf
CFLAGS=-g -Wall -Wextra -Werror
LFLAGS=-I includes/

SRC_FILES =		main.c \
				shell/shell.c \
				shell/shell_utils.c \
				shell/shell_utils_2.c \
				shell/shell_utils_3.c \
				builtin/ft_env.c \
				builtin/ft_cd/ft_cd.c \
				builtin/ft_cd/ft_cd_utils.c \
				builtin/ft_echo.c \
				builtin/ft_pwd.c \
				builtin/ft_unset.c \
				builtin/ft_export/ft_export.c \
				builtin/ft_export/ft_export_utils.c \
				builtin/ft_export/ft_export_utils_2.c \
				builtin/ft_exit.c \
				parsing/backslash.c \
				parsing/braces.c \
				parsing/embrace_expansion.c \
				parsing/expansion.c \
				parsing/parser.c \
				parsing/quotes.c \
				parsing/quotes_utils.c \
				parsing/split_non_escaped.c \
				validator/validator.c \
				validator/validator_utils.c \
				get_next_line.c \
				search.c \
				signals.c \
				errors.c \
				clean.c \
				utils.c \
				redirections.c \
				pipes.c \
				permissions.c \
				shlvl.c \
			
OBJ_FILES=$(SRC_FILES:.c=.o)
SRC_DIR=srcs/
OBJ_DIR=objs/
LIB_DIR=libft
OBJS=$(addprefix $(OBJ_DIR), $(OBJ_FILES))


all: 			$(OBJ_DIR) $(NAME)

$(OBJ_DIR):		
				@mkdir -p $(OBJ_DIR)
				@mkdir -p $(OBJ_DIR)/shell
				@mkdir -p $(OBJ_DIR)/builtin
				@mkdir -p $(OBJ_DIR)/builtin/ft_cd
				@mkdir -p $(OBJ_DIR)/builtin/ft_export
				@mkdir -p $(OBJ_DIR)/parsing
				@mkdir -p $(OBJ_DIR)/validator

$(NAME): 		$(OBJS)
				@make -C $(LIB_DIR)
				@$(CC) $(CFLAGS) $(LFLAGS) $(OBJS) -Llibft -lft -o $(NAME)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
				@$(CC) $(LFLAGS) $(CFLAGS) -c $< -o $@

clean:	
				@make clean -C $(LIB_DIR)
				@$(RM) $(OBJ_DIR)

fclean: 		clean
				@make fclean -C $(LIB_DIR)
				@$(RM) $(NAME)
				@$(RM) $(NAME).dSYM

re: 			fclean all

run:			
				./minishell

.PHONY: all clean fclean re
