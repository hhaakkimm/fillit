#ifndef FILLIT_H
# define FILLIT_H
# include <string.h>
# include "libft/libft.h"

typedef struct	s_map
{
	char		**array;
}				table;
typedef struct	s_etris
{
	char		**pos;
	int			width;
	int			height;
	char		letter;
}				t_tetr;

void			reverse(t_list **alst);
t_list			*init(int fd);
int             get_size(table *x);
void			free_map(table *map);
t_tetr		    *tetris_new(char **pos, int width, int height, char letter);
table			*map_new(int size);
void			set(t_tetr *tetri, table *map, int x, int y, char c);
table			*solve(t_list *list);
t_list			*free_list(t_list *list);
#endif