# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iderighe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/27 10:55:19 by iderighe          #+#    #+#              #
#    Updated: 2022/02/03 15:17:10 by iderighe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

CC		=	clang
CFLAGS	=	-Wall -Wextra -Werror -pthread
CTHR	=	-fsanitize=thread -g3
CFS		=	-fsanitize=address -g3

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
			$(CC) $(CFLAGS) $(CFS) -o $(NAME) $(SRC)

fst		:	$(OBJ)
			$(CC) $(CFLAGS) $(CTHR) -o $(NAME) $(SRC)

fre		:	fclean f

re		:	fclean all

.PHONY	:	all norm clean fclean fsa fst fre re
