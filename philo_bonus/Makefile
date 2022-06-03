# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olakhdar <olakhdar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/06 16:36:12 by olakhdar          #+#    #+#              #
#    Updated: 2022/06/03 20:35:54 by olakhdar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

CC = gcc

FLAGS =  -Wall -Werror -Wextra

FILES = philo_bonus.c philo_data.c ft_atoi.c error_bonus.c supervisor_bonus.c \

OBJ=$(FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all 
