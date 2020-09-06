NAME=minishell

CC=gcc
RM = rm -rf
CFLAGS=-g -Wall -Wextra -Werror
LFLAGS=-I includes/

SRC_FILES =		main.c \
				get_next_line.c \
				get_next_line_utils.c \
				parser.c \
				search.c \
				ft_env.c \
				ft_cd.c \
				signals.c
			
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
				@make -C $(LIB_DIR) clean
				@$(RM) $(OBJ_DIR)

fclean: 		clean
				@make -C $(LIB_DIR) fclean
				@$(RM) $(NAME)

re: 			fclean all

run:			
				./minishell

.PHONY: all clean fclean re
