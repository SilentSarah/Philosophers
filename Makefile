# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/28 16:43:35 by hmeftah           #+#    #+#              #
#    Updated: 2023/03/10 20:02:43 by hmeftah          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
FLAGS = -Wall -Werror -Wextra
INCLUDE = -I Philosophers.h
SRC = dine.c dine_tools.c load_data.c monitor.c mutex_philo_tools.c utilities.c utilities_2.c
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