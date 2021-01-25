NAME=minishell

CC=gcc
RM = rm -rf
CFLAGS=-g -Wall -Wextra -Werror
LFLAGS=-I includes/

SRC_FILES =		main.c \
				get_next_line.c \
				parser.c \
				search.c \
				ft_env.c \
				ft_cd.c \
				ft_echo.c \
				ft_pwd.c \
				ft_unset.c \
				ft_export.c \
				ft_exit.c \
				signals.c \
				errors.c \
				clean.c \
				expansion.c \
				embrace_expansion.c \
				utils.c \
				quotes.c \
				backslash.c \
				quotes_utils.c \
				split_non_escaped.c \
				redirections.c \
				pipes.c \
				permissions.c \
				ft_shlvl.c
			
OBJ_FILES=$(SRC_FILES:.c=.o)
SRC_DIR=srcs
OBJ_DIR=objs
LIB_DIR=libft
SRC=$(SRC_FILES:%=$(SRC_DIR)/%)
OBJS=$(OBJ_FILES:%=$(OBJ_DIR)/%)


all: 			$(OBJ_DIR) $(NAME)

$(OBJ_DIR):		
				@mkdir -p $(OBJ_DIR)

$(NAME): 		$(OBJS)
				@make -C $(LIB_DIR)
				@$(CC) $(CFLAGS) $(LFLAGS) -Llibft -lft $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
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
