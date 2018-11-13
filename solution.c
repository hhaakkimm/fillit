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

#include "fillit.h"

int		to_try(t_tetr *tetri, char **map, int x, int y)
{
	int i;
	int j;
	int a[2];

	i = 0;
	a[0] = x;
	a[1] = y;
	while (i < tetri->width)
	{
		j = 0;
		while (j < tetri->height)
		{
			if (tetri->pos[j][i] == '#' && map[y + j][x + i] != '.')
				return (0);
			j++;
		}
		i++;
	}
	set(tetri, map, a, tetri->letter);
	return (1);
}

int		get_size(char **x)
{
	int i;

	i = 0;
	while (x[0][i])
		i++;
	return (i);
}

int		solve_map(char **map, t_list *list)
{
	int			sz;
	int			a[2];
	t_tetr		*tetri;

	a[1] = 0;
	sz = get_size(map);
	tetri = (t_tetr *)(list->content);
	while (a[1] < sz - tetri->height + 1)
	{
		a[0] = 0;
		while (a[0] < sz - tetri->width + 1)
		{
			if (to_try(tetri, map, a[0], a[1]))
			{
				if (!list->next || solve_map(map, list->next))
					return (1);
				else
					set(tetri, map, a, '.');
			}
			a[0]++;
		}
		a[1]++;
	}
	return (0);
}

char	**solve(t_list *list)
{
	char	**map;
	int		size;

	size = ft_sqrt(ft_lstcount(list) * 4);
	map = map_new(size);
	if (!list)
		return (map);
	while (!solve_map(map, list))
	{
		size++;
		free_map(map);
		map = map_new(size);
	}
	return (map);
}
