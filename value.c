/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetrimino.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdrakh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 00:15:56 by aabdrakh          #+#    #+#             */
/*   Updated: 2018/11/07 00:15:58 by aabdrakh         ###   ########.fr       */
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

t_list		*free_list(t_list *list)
{
	t_tetr	*tetris;
	t_list	*next;

	while (list)
	{
		tetris = (t_tetr *)list->content;
		next = list->next;
		free_tetris(tetris);
		ft_memdel((void **)&list);
		list = next;
	}
	return (NULL);
}

void		free_tetris(t_tetr *tetri)
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
