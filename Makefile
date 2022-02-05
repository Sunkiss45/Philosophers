# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebarguil <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/04 13:26:27 by ebarguil          #+#    #+#              #
#    Updated: 2022/02/05 20:03:02 by ebarguil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

INC		=	includes/philo.h

SRCS	=	srcs/main.c \
			srcs/parsing.c \
			srcs/manager.c \
			srcs/philosophe.c \
			srcs/bigbrother.c \
			srcs/end.c \
			srcs/utils.c

CC		=	clang
CFLAGS	=	-Wall -Wextra -Werror -pthread -I./includes
FSAN-AD	=	-fsanitize=address -g3
FSAN-TH	=	-fsanitize=thread

RM		=	/usr/bin/rm -rf

OBJS	=	$(SRCS:.c=.o)

all		:	$(NAME)

$(NAME)	:	$(OBJS)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o		:	%.c $(INC)
			$(CC) -o $@ -c $< $(CFLAGS)

n		:
			norminette $(SRCS)
			norminette $(INC)

clean	:
			$(RM) $(OBJS)

fclean	:	clean
			$(RM) $(NAME)

fare	:	fclean $(OBJS)
			$(CC) $(CFLAGS) $(FSAN-AD) -o $(NAME) $(OBJS)

ftre	:	fclean $(OBJS)
			$(CC) $(CFLAGS) $(FSAN-TH) -o $(NAME) $(OBJS)

re		:	fclean all

.PHONY	:	all n clean fclean fare ftre re
