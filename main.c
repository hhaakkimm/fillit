/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdrakh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 20:08:06 by aabdrakh          #+#    #+#             */
/*   Updated: 2018/11/12 20:08:07 by aabdrakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void		reverse(t_list **alst)
{
	t_list	*prev;
	t_list	*cur;
	t_list	*next;

	prev = NULL;
	cur = *alst;
	while (cur != NULL)
	{
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}
	*alst = prev;
}

void		free_table(t_tetr *tetri)
{
	int y;

	y = 0;
	while (y < tetri->height)
	{
		ft_memdel((void **)(&(tetri->pos[y])));
		y++;
	}
	ft_memdel((void **)(&(tetri->pos)));
	ft_memdel((void **)&tetri);
}

t_list		*free_list(t_list *list)
{
	t_tetr	*tetris;
	t_list	*next;

	while (list)
	{
		tetris = (t_tetr *)list->content;
		next = list->next;
		free_table(tetris);
		ft_memdel((void **)&list);
		list = next;
	}
	return (NULL);
}

t_tetr		*tetris_new(char **pos, int width, int height, char letter)
{
	t_tetr		*tetris;

	tetris = ft_memalloc(sizeof(t_tetr));
	tetris->pos = pos;
	tetris->width = width;
	tetris->height = height;
	tetris->letter = letter;
	return (tetris);
}

int			main(int argc, char **argv)
{
	t_list		*list;
	char		**map;
	int			fd;
	int			i;
	int			sz;

	if (argc != 2)
	{
		ft_putstr("usage: fillit input_file\n");
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (!(list = init(fd)))
	{
		ft_putstr("error");
		return (1);
	}
	map = solve(list);
	i = 0;
	sz = get_size(map);
	while (i < sz)
		ft_putstr(map[i++]);
	free_map(map);
	free_list(list);
	return (0);
}
