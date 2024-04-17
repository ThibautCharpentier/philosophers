# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/26 12:21:41 by tcharpen          #+#    #+#              #
#    Updated: 2022/07/26 12:21:41 by tcharpen         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = philo

HDR = srcs/philosophers.h

SRCS = utils/atoi_philo.c utils/ft_putchar_fd.c utils/ft_putnbr_fd.c \
utils/ft_strlen.c utils/utils.c \
free.c init.c main.c philo.c thread.c

OBJS = ${addprefix srcs/,${SRCS:.c=.o}}

LIB = -lpthread

CC = gcc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g3

%.o: %.c ${HDR} Makefile
	${CC} ${CFLAGS} -c $< -o $@

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIB}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
