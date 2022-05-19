# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olakhdar <olakhdar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/06 16:36:12 by olakhdar          #+#    #+#              #
#    Updated: 2022/05/19 16:28:53 by olakhdar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc

FLAGS =  -Wall -Werror -Wextra -pthread

FILES = philosophers.c philo_lists.c ft_atoi.c \

all: $(NAME)

$(NAME):
	$(CC) $(FLAGS) $(FILES) -o $(NAME)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all 
	