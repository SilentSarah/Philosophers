# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/28 16:43:35 by hmeftah           #+#    #+#              #
#    Updated: 2023/02/28 18:05:14 by hmeftah          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
FLAGS = -Wall -Werror -Wextra
INCLUDE = -I Philosophers.h
SRC = main.c utilities.c actions.c
PTHREAD = -pthread

all: mand

mand: $(NAME) $(SRC)

$(NAME): $(SRC)
	@echo "Building Executables"
	@$(CC) $(FLAGS) $(INCLUDE) $(PTHREAD) $(SRC) -o $@

clean:
	@echo "Deleting Executables"
	@rm -rf philo

fclean: clean

re: fclean all

.PHONY: all mand clean fclean re