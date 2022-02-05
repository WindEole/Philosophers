# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iderighe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/27 10:55:19 by iderighe          #+#    #+#              #
#    Updated: 2022/02/04 13:57:55 by iderighe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

CC		=	clang
CFLAGS	=	-Wall -Wextra -Werror -pthread
CFA		=	-fsanitize=address -g3
CFT		=	-fsanitize=thread -g3

RM		=	/usr/bin/rm -rf

SRC		=	main_philo.c \
			philo_thread.c \
			init.c \
			time.c \
			print.c \
			end.c \

OBJ		=	$(SRC:.c=.o)


all		:	$(NAME)

$(NAME)	:	$(OBJ)
			$(CC) $(CFLAGS) -o $(NAME) $(SRC)

%.o		:	%.c
			$(CC) -o $@ -c $< $(CFLAGS)

norm	:
			norminette $(SRC)
			norminette philo.h

clean	:
			$(RM) $(OBJ)

fclean	:	clean
			$(RM) $(NAME)

fsa		:	$(OBJ)
			$(CC) $(CFLAGS) $(CFA) -o $(NAME) $(SRC)

fst		:	$(OBJ)
			$(CC) $(CFLAGS) $(CFT) -o $(NAME) $(SRC)

re		:	fclean all

.PHONY	:	all norm clean fclean fsa fst re
