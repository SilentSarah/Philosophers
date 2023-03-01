# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/28 16:43:35 by hmeftah           #+#    #+#              #
#    Updated: 2023/03/01 16:53:32 by hmeftah          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
FLAGS = -Wall -Werror -Wextra
INCLUDE = -I Philosophers.h
SRC = utilities.c actions.c monitor.c
MAIN = main.c
PTHREAD = -pthread

all: mand

mand: $(NAME) $(SRC:.c=.o)

%.o: %.c
	@echo "Building Object File: |	$< |"
	@$(CC) $(FLAGS) $(PTHREAD) $< -c -o $@

$(NAME): $(SRC:.c=.o) $(MAIN)
	@echo "Building Executables"
	@$(CC) $(FLAGS) $(INCLUDE) $(PTHREAD) $(SRC:.c=.o) $(MAIN) -o $@

clean:
	@echo "Deleting Object Files"
	@rm -rf *.o

fclean: clean
	@echo "Deleting Executables"
	@rm -rf philo

re: fclean all

.PHONY: all mand clean fclean re