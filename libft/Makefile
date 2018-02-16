# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/28 17:18:59 by rfabre            #+#    #+#              #
#    Updated: 2018/02/06 15:58:55 by rfabre           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY : all clean fclean re
NAME = libft.a
SRC = ft_bzero.c\
	  ft_isascii.c\
	  ft_isprint.c\
	  ft_strcmp.c\
	  ft_strcpy.c\
	  ft_strncmp.c\
	  ft_strncpy.c\
	  ft_tolower.c\
	  ft_toupper.c\
	  ft_strlen.c\
	  ft_strdup.c\
	  ft_isalpha.c\
	  ft_isdigit.c\
	  ft_isalnum.c\
	  ft_memccpy.c\
	  ft_memcpy.c\
	  ft_memmove.c\
	  ft_memchr.c\
	  ft_strcat.c\
	  ft_strncat.c\
	  ft_strchr.c\
	  ft_strrchr.c\
	  ft_memcmp.c\
	  ft_atoi.c\
	  ft_strstr.c\
	  ft_strnstr.c\
	  ft_memalloc.c\
	  ft_memset.c\
	  ft_memdel.c\
	  ft_strlcat.c\
	  ft_strnew.c\
	  ft_strdel.c\
	  ft_strclr.c\
	  ft_striter.c\
	  ft_striteri.c\
	  ft_strmap.c\
	  ft_strmapi.c\
	  ft_strequ.c\
	  ft_strnequ.c\
	  ft_strsub.c\
	  ft_strjoin.c\
	  ft_isspace.c\
	  ft_strtrim.c\
	  ft_putchar.c\
	  ft_putstr.c\
	  ft_itoa.c\
	  ft_putendl.c\
	  ft_putchar_fd.c\
	  ft_putstr_fd.c\
	  ft_putendl_fd.c\
	  ft_putnbr_fd.c\
	  ft_putnbr.c\
	  ft_strsplit.c\
	  ft_lstnew.c\
	  ft_lstdelone.c\
	  ft_lstdel.c\
	  ft_lstadd.c\
	  ft_lstiter.c\
	  ft_lstmap.c\
	  ft_lstaddend.c\
	  ft_strndup.c\
	  ft_strjoinmulti.c\
	  ft_strcspn.c\
	  ft_putnstr.c\
	  ft_freejoinstr.c\
	  ft_freearraystr.c\
		ft_strjoinnfree.c

OBJDIR = objs
HEADERFLAGS = -I libft.h
CC = @gcc
CFLAGS = -Werror -Wall -Wextra
OBJ = $(addprefix ${OBJDIR}/, $(SRC:.c=.o))
RM = rm -f

all : $(NAME)

$(NAME) : $(OBJ)
	@echo "\t\033[33;32m'MAKE' ->\t\033[1;34m$(NAME)\033[0m :\tLibrary compilation in progress..."

	@ar rcs $(NAME) $(OBJ)

	@echo "\t\033[33;32m'MAKE' ->\t\033[1;34m$(NAME)\033[0m :\tLibrary compilation completed successfully !"

${OBJDIR}/%.o : ./%.c
	@/bin/mkdir -p ${OBJDIR}
	@${CC} ${CFLAGS} -I./includes -c -o $@ $<

clean :
	@echo "\t\033[1;31m'CLEAN' ->\tDestruction\033[0m:\tfiles .o for the library \033[1;34m$(NAME)\033[0m"
	@rm -rf $(OBJDIR)
	@echo "\t\033[1;31m'CLEAN' ->\tDestruction\033[0m:\tfiles .o for the library \033[1;34m$(NAME)\033[0m completed successfully !"

fclean : clean
	@$(RM) $(NAME)
	@echo "\t\033[1;31m'FCLEAN' ->\tDestruction\033[0m     library \033[1;34m$(NAME)\033[0m completed successfully !"

re : fclean all
