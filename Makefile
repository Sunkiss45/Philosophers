# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebarguil <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/04 13:26:27 by ebarguil          #+#    #+#              #
#    Updated: 2022/02/05 10:50:10 by ebarguil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

CC		=	clang
CF		=	-Wall -Wextra -Werror -pthread
FA		=	-fsanitize=address -g3
FT		=	-fsanitize=thread -g3

RM		=	/usr/bin/rm -rf

SRC		=	main_philo.c \
			check.c \
			philo_thread.c \
			init.c \
			time.c \
			print.c \
			end.c \

OBJ		=	$(SRC:.c=.o)


all		:	$(NAME)

$(NAME)	:	$(OBJ)
			$(CC) $(CF) -o $(NAME) $(SRC)

%.o		:	%.c
			$(CC) -o $@ -c $< $(CF)

n		:
			norminette $(SRC)
			norminette philo.h

clean	:
			$(RM) $(OBJ)

fclean	:	clean
			$(RM) $(NAME)

fa		:	$(OBJ)
			$(CC) $(CF) $(FA) -o $(NAME) $(SRC)

ft		:	$(OBJ)
			$(CC) $(CF) $(FT) -o $(NAME) $(SRC)

fare	:	fclean fa

ftre	:	fclean ft

re		:	fclean all

.PHONY	:	all norm clean fclean fa ft fare ftre re
