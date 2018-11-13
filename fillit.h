/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdrakh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 18:44:16 by aabdrakh          #+#    #+#             */
/*   Updated: 2018/11/12 18:44:17 by aabdrakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# include <string.h>
# include <fcntl.h>
# include <stdio.h>
# include "libft/libft.h"
# include <unistd.h>

typedef struct	s_etris
{
	char		**pos;
	int			width;
	int			height;
	char		letter;
}				t_tetr;

void			reverse(t_list **alst);
t_list			*init(int fd);
int				get_size(char **x);
void			free_map(char **map);
t_tetr			*tetris_new(char **pos, int width, int height, char letter);
char			**map_new(int size);
void			set(t_tetr *tetri, char **map, int *a, char c);
char			**solve(t_list *list);
t_list			*free_list(t_list *list);
#endif
