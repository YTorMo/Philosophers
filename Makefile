# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytoro-mo < ytoro-mo@student.42malaga.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/19 08:56:23 by ytoro-mo          #+#    #+#              #
#    Updated: 2023/02/09 13:13:35 by ytoro-mo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	philo/philo
NAME_BONUS		=	philo_bonus/philo_bonus
CFLAGS			=	-w -Wall -Werror -Wextra
#USER			=	ytoro-mo

HEADERS			=	philo/include/philosopher.h
HEADERS_BONUS	=	philo_bonus/include/philosopher_bonus.h
SRCS			=	philo/src/init.c philo/src/main.c philo/src/utils.c
SRCS_BONUS		=	philo_bonus/src/init_bonus.c philo_bonus/src/main_bonus.c philo_bonus/src/utils_bonus.c
OBJS			=	${SRCS:.c=.o}
OBJS_BONUS		=	${SRCS_BONUS:.c=.o}
#SRCS	= $(shell find ./src -iname "*.c")


BOLD	= \033[1m
GREEN	= \033[32;1m
RESET	= \033[0m

all: $(NAME)

$(NAME): $(SRCS) $(OBJS) $(HEADERS)
	@cc $(CFLAGS) $(SRCS) -o $(NAME)

%.o: %.c
	@cc $(CFLAGS) -c $< -o $@ && printf "${GREEN}$(BOLD)\rCompiling: $(notdir $<)\r\e[35C[OK]\n$(RESET)"

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(HEADERS_BONUS) $(OBJS_BONUS) $(SRCS_BONUS)
	@cc $(CFLAGS) $(SRCS_BONUS) -o $(NAME_BONUS)

clean:
	@rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS)
	
re: fclean all

.PHONY: all, clean, fclean, re
