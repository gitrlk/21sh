# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/19 14:14:34 by jecarol           #+#    #+#              #
#    Updated: 2018/01/25 20:40:12 by rfabre           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME = 21sh

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS_LIST = main.c line_movement.c line_editing.c copy_paste.c term.c line_edit2.c env.c history.c

SRCS_DIR = srcs/
SRCS = $(addprefix $(SRCS_DIR), $(SRCS_LIST))

OBJS_DIR = objs/
OBJS_LIST = $(patsubst %.c, %.o, $(SRCS_LIST))
OBJS = $(addprefix $(OBJS_DIR), $(OBJS_LIST))

HEADERS = -I./libft -I./includes

LIB = -L./libft -lft

# COLOR
C_GOOD = "\033[32m"
C_DURING = "\033[36m"

# MESSAGE
SUCCESS = $(C_GOOD)COMPILATION SUCCEEDED

all: $(NAME)

$(NAME): $(OBJS)
	@make -C ./libft/
	@echo $(C_DURING)"Compiling" [ $(NAME) . . . ]
	@$(CC) $(CFLAGS) $^ $(LIB) -o $(NAME) -ltermcap
	@echo $(SUCCESS)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
		@/bin/rm -rf $(OBJS_DIR)
		@make clean -C libft/
		@echo $(C_GOOD)"OBJ FILES DELETED"

fclean: clean
		@/bin/rm -rf $(NAME)
		@make fclean -C libft/
		@echo $(C_GOOD)"EXECUTABLE FILE DELETED"

re: fclean all
