NAME=minishell

CC=gcc
RM = rm -rf
CFLAGS=-Wall -Wextra -Werror

SRC_FILES=main.c
OBJ_FILES=$(SRC_FILES:.c=.o)
SRC_DIR=srcs
OBJ_DIR=objs
SRC=$(SRC_FILES:%=$(SRC_DIR)/%)
OBJS=$(OBJ_FILES:%=$(OBJ_DIR)/%)


all: 			$(OBJ_DIR) $(NAME)

$(OBJ_DIR):		
				mkdir -p $(OBJ_DIR)

$(NAME): 		$(OBJS)

clean:	
				$(RM) $(OBJ_DIR)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
				$(CC) $(CFLAGS) -c $< -o $@

fclean: 		clean
				$(RM) $(NAME)

re: fclean all
