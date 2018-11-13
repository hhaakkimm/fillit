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

void	free_map(char **map)
{
	int i;
	int sz;

	i = 0;
	sz = get_size(map);
	while (i < sz)
	{
		ft_memdel((void **)&(map[i]));
		i++;
	}
	ft_memdel((void **)&(map));
	ft_memdel((void **)&map);
}

char	**map_new(int size)
{
	char	**map;
	int		i;
	int		j;

	map = (char **)ft_memalloc(sizeof(char *) * size);
	i = 0;
	while (i < size)
	{
		map[i] = ft_strnew(size);
		j = 0;
		while (j < size)
		{
			map[i][j] = '.';
			j++;
		}
		i++;
	}
	return (map);
}

void	set(t_tetr *tetri, char **map, int *a, char c)
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
				map[a[1] + j][a[0] + i] = c;
			j++;
		}
		i++;
	}
}
