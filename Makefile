# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytoro-mo < ytoro-mo@student.42malaga.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/19 08:56:23 by ytoro-mo          #+#    #+#              #
#    Updated: 2023/02/08 14:30:56 by ytoro-mo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo
CFLAGS	=	-w -Wall -Werror -Wextra
#USER	=	ytoro-mo

HEADERS	=	-I ./include
SRCS	=	src/init.c src/main.c src/utils.c
OBJS	=	${SRCS:.c=.o}
#SRCS	= $(shell find ./src -iname "*.c")


BOLD	= \033[1m
GREEN	= \033[32;1m
RESET	= \033[0m

all: $(NAME)

%.o: %.c
	@gcc $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "${GREEN}$(BOLD)\rCompiling: $(notdir $<)\r\e[35C[OK]\n$(RESET)"

$(NAME): $(OBJS)
	@gcc $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)
	
re: clean all

.PHONY: all, clean, fclean, re
