/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdrakh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 20:08:25 by aabdrakh          #+#    #+#             */
/*   Updated: 2018/11/12 20:08:27 by aabdrakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	get_mm(char *str, int *a)
{
	int i;

	i = 0;
	while (i < 20)
	{
		if (str[i] == '#')
		{
			a[0] = ft_min(i / 5, a[0]);
			a[2] = ft_max(i / 5, a[2]);
			a[1] = ft_min(i % 5, a[1]);
			a[3] = ft_max(i % 5, a[3]);
		}
		i++;
	}
}

t_tetr	*get(char *str, char letter)
{
	int			a[4];
	char		**pos;
	int			i;
	t_tetr		*tetri;

	a[0] = 3;
	a[1] = 3;
	a[2] = 0;
	a[3] = 0;
	get_mm(str, a);
	pos = ft_memalloc(sizeof(char *) * (a[2] - a[0] + 1));
	i = 0;
	while (i < a[2] - a[0] + 1)
	{
		pos[i] = ft_strnew(a[3] - a[1] + 1);
		ft_strncpy(pos[i], str + (a[1]) + (i + a[0]) * 5, a[3] - a[1] + 1);
		i++;
	}
	tetri = tetris_new(pos, a[3] - a[1] + 1, a[2] - a[0] + 1, letter);
	return (tetri);
}

int		checker(char *buf)
{
	int i;
	int	amount_of_connection;
	int	amount_heshteg;

	i = 0;
	amount_heshteg = 0;
	amount_of_connection = 0;
	while (buf[i])
	{
		if (buf[i] == '#' && ++amount_heshteg)
		{
			if ((i + 1) < 20 && buf[i + 1] == '#')
				amount_of_connection++;
			if ((i - 1) >= 0 && buf[i - 1] == '#')
				amount_of_connection++;
			if ((i + 5) < 20 && buf[i + 5] == '#')
				amount_of_connection++;
			if ((i - 5) >= 0 && buf[i - 5] == '#')
				amount_of_connection++;
		}
		i++;
	}
	return ((amount_heshteg != 4 || (amount_of_connection != 6 &&
	amount_of_connection != 8)) ? 0 : 1);
}

int		valid(char *str, int len)
{
	int i;

	i = 0;
	while (i < 20)
	{
		if (i % 5 < 4 && str[i] != '#' && str[i] != '.')
			return (1);
		else if (i != 19 && i % 5 == 4 && str[i] != '\n')
			return (1);
		i++;
	}
	if (!checker(str) || (len == 21 && str[20] != '\n'))
		return (1);
	return (0);
}

t_list	*init(int fd)
{
	char	buf[21];
	int		let;
	int		length;
	t_list	*list;
	t_tetr	*tetris;

	let = 0;
	ft_memset(buf, '\0', 21);
	list = NULL;
	while ((length = read(fd, buf, 21)) >= 19)
	{
		if (valid(buf, length) || (tetris = get(buf, (let + 'A'))) == NULL)
			return (free_list(list));
		ft_lstadd(&list, ft_lstnew(tetris, sizeof(t_tetr)));
		ft_memdel((void **)&tetris);
		let++;
	}
	if (length)
	{
		return (free_list(list));
	}
	reverse(&list);
	return (list);
}
