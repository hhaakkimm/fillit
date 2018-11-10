# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dezzeddi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/28 14:26:29 by dezzeddi          #+#    #+#              #
#    Updated: 2018/04/28 17:10:34 by dezzeddi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

FLAGS=-Wall -Wextra -Werror -g

SRCS=main.c place_tet_on_map.c map.c read.c validation.c transform.c
OBJ = $(patsubst %.c,%.o,$(SRCS))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	gcc -I libft/includes -L libft/ -lft $(FLAGS) $(OBJ) -o $(NAME)

$(OBJ):
	make -C libft
	gcc -I libft/includes -c $(FLAGS) $(SRCS)

clean:
	make -C libft clean
	rm -f $(OBJ)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all
