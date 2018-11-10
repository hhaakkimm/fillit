/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdrakh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 00:16:12 by aabdrakh          #+#    #+#             */
/*   Updated: 2018/11/07 00:16:14 by aabdrakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft/libft.h"
#include "fillit.h"

int		to_try(t_tetr *tetri, table *map, int x, int y)
{
	int i;
	int j;

	i = 0;
	while (i < tetri->width)
	{
		j = 0;
		while (j < tetri->height)
		{
			if (tetri->pos[j][i] == '#' && map->array[y + j][x + i] != '.')
				return (0);
			j++;
		}
		i++;
	}
	set(tetri, map, x, y, tetri->letter);
	return (1);
}

int		get_size(table *x)
{
	int i;

	i = 0;
	while (x->array[0][i])
		i++;
	return (i);
}

int		solve_map(table *map, t_list *list)
{
	int			x;
	int			y;
	int			sz;
	t_tetr		*tetri;

	if (list == NULL)
		return (1);
	y = 0;
	sz = get_size(map);
	tetri = (t_tetr *)(list->content);
	while (y < sz - tetri->height + 1)
	{
		x = 0;
		while (x < sz - tetri->width + 1)
		{
			if (to_try(tetri, map, x, y))
			{
				if (solve_map(map, list->next))
					return (1);
				else
					set(tetri, map, x, y, '.');
			}
			x++;
		}
		y++;
	}
	return (0);
}

table	*solve(t_list *list)
{
	table	*map;
	int		size;

	size = ft_sqrt(ft_lstcount(list) * 4);
	map = map_new(size);
	while (!solve_map(map, list))
	{
		size++;
		free_map(map);
		map = map_new(size);
	}
	return (map);
}
