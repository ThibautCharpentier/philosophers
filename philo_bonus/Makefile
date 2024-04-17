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

NAME = philo_bonus

HDR = srcs/philosophers_bonus.h

SRCS = utils/atoi_philo_bonus.c utils/ft_putchar_fd_bonus.c \
utils/ft_putnbr_fd_bonus.c utils/ft_strlen_bonus.c utils/utils_bonus.c \
free_bonus.c init_bonus.c main_bonus.c philo_bonus.c fork_bonus.c \
thread_bonus.c

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
