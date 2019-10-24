//
// Created by kitos on 15.10.2019.
//

# include "../lem-in.h"

static int ft_find_col_links(t_room *room)
{
	int col_links;
	t_links_room *link;

	col_links = 0;
	link = room->links_room;
	while (link != NULL)
	{
		col_links++;
		link= link->next;
	}
	return (col_links);
}

static void ft_record_links_mas(t_room *room, int col)
{
	t_links_room	*link;
	int 			i;

	i = 0;
	link = room->links_room;
	while (i < col)
	{
		room->mas_links[i] = link->name_int;
		link = link->next;
		i++;
	}
}

void	ft_built_int_mas_links(void)
{
	int	i;
	int col;

	i = -1;
	while (basic_info_rooms->mas_rooms[++i] != NULL)
	{
		col = ft_find_col_links(basic_info_rooms->mas_rooms[i]);
		basic_info_rooms->mas_rooms[i]->col_links = col;
		basic_info_rooms->mas_rooms[i]->mas_links = (int *)malloc(sizeof(int) * col);
		ft_record_links_mas(basic_info_rooms->mas_rooms[i], col);
	}
}

