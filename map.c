/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdrakh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 00:15:45 by aabdrakh          #+#    #+#             */
/*   Updated: 2018/11/07 00:15:46 by aabdrakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft/libft.h"

void	free_map(table *map)
{
	int i;
	int sz;

	i = 0;
	sz = get_size(map);
	while (i < sz)
	{
		ft_memdel((void **)&(map->array[i]));
		i++;
	}
	ft_memdel((void **)&(map->array));
	ft_memdel((void **)&map);
}

table	*map_new(int size)
{
	table	*map;
	int		i;
	int		j;

	map = (table *)ft_memalloc(sizeof(table));
	map->array = (char **)ft_memalloc(sizeof(char *) * size);
	i = 0;
	while (i < size)
	{
		map->array[i] = ft_strnew(size);
		j = 0;
		while (j < size)
		{
			map->array[i][j] = '.';
			j++;
		}
		i++;
	}
	return (map);
}

void	set(t_tetr *tetri, table *map, int x, int y, char c)
{
	int i;
	int j;

	i = 0;
	while (i < tetri->width)
	{
		j = 0;
		while (j < tetri->height)
		{
			if (tetri->pos[j][i] == '#')
				map->array[y + j][x + i] = c;
			j++;
		}
		i++;
	}
}
