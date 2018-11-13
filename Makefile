# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aabdrakh <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/12 19:50:20 by aabdrakh          #+#    #+#              #
#    Updated: 2018/11/12 19:50:21 by aabdrakh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

SRC = main.c solution.c validate.c map.c

OBJ = $(SRC:.c=.o)

INC = -I includes

LIBFT =	libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
		gcc -Wall -Wextra -Werror $(OBJ) -o $(NAME) $(LIBFT)

$(OBJ): $(LIBFT)
		gcc -Wall -Wextra -Werror $(FLAGS) -c $(SRC)

$(LIBFT):
		make -C ./libft/

clean:
		rm -f $(OBJ)
			make clean -C ./libft/

fclean: clean
		rm -f $(NAME)
			make fclean -C ./libft/

re: fclean all

.PHONY : all, re, clean, flcean