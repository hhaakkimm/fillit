/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdrakh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 00:16:04 by aabdrakh          #+#    #+#             */
/*   Updated: 2018/11/07 00:16:06 by aabdrakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft/libft.h"
#include "fillit.h"

void	get_mm(char *str, int *r_mn, int *c_mn, int *r_mx, int *c_mx)
{
	int i;

	i = 0;
	while (i < 20)
	{
		if (str[i] == '#')
		{
			*r_mn = ft_min(i / 5, *r_mn);
			*r_mx = ft_max(i / 5, *r_mx);
			*c_mn = ft_min(i % 5, *c_mn);
			*c_mx = ft_max(i % 5, *c_mx);
		}
		i++;
	}
}

t_tetr	*get(char *str, char letter)
{
	int			r_mn;
	int			r_mx;
	int			c_mn;
	int			c_mx;
	char		**pos;
	int			i;
	t_tetr		*tetri;

	r_mn = 3;
	c_mn = 3;
	r_mx = 0;
	c_mx = 0;
	get_mm(str, &r_mn, &c_mn, &r_mx, &c_mx);
	pos = ft_memalloc(sizeof(char *) * (r_mx - r_mn + 1));
	i = 0;
	while (i < r_mx - r_mn + 1)
	{
		pos[i] = ft_strnew(c_mx - c_mn + 1);
		ft_strncpy(pos[i], str + (c_mn) + (i + r_mn) * 5, c_mx - c_mn + 1);
		i++;
	}
	tetri = tetris_new(pos, c_mx - c_mn + 1, r_mx - r_mn + 1, letter);
	return (tetri);
}

int checker(char *buf)
{
    int i = 0;
    int amount_of_connection = 0;
    int amount_heshteg = 0;

    while(buf[i])
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
    if (amount_heshteg != 4 || (amount_of_connection != 6 && amount_of_connection != 8))
		return (0);
	return (1);
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
	char    buf[21];
	int		let;
	int		length;
	int 	prev;
	t_list	*list;
	t_tetr	*tetris;

	let = 0;
	ft_memset(buf, '\0', 21);
	list = NULL;
	while ((length = read(fd, buf, 21)) >= 19)
	{
		prev = length;
		if (valid(buf, length) || (tetris = get(buf, (let + 'A'))) == NULL)
			return (free_list(list));
		ft_lstadd(&list, ft_lstnew(tetris, sizeof(t_tetr)));
		ft_memdel((void **)&tetris);
		let++;
	}
	if (length || prev != 19)
		return (free_list(list));
	reverse(&list);
	return (list);
}