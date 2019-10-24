//
// Created by kitos on 14.10.2019.
//

#include "../lem-in.h"

static t_room *ft_find_room(char *str)
{
	t_room	*room;

	room = basic_info_rooms->room;
	while (room != NULL)
	{
		if (ft_strcmp(str, room->name_str) == 0)
			return (room);
		room = room->next;
	}
	return (NULL);
}

static void ft_record_link(void)
{
	t_room			*list;
	t_room			*room;
	t_links_room	*link;

	room = basic_info_rooms->room;
	while (room != NULL)
	{
		link = room->links_room;
		while (link != NULL)
		{
			if ((list = ft_find_room(link->name_str)) == NULL)
				ft_exit();
			link->name_int = list->name_int;
			link = link->next;
		}
		room = room->next;
	}
}

static void ft_finish_graph(t_room *room, int col_room)
{
	t_room	**mas_room;
	int 	i;

	i = 0;
	if (!(mas_room = (t_room	**)malloc(sizeof(t_room *) * (col_room + 1))))
		ft_exit();
	mas_room[col_room] = NULL;
	while (room != NULL)
	{
		room->name_int = i;
		mas_room[i++] = room;
		room = room->next;
	}
	basic_info_rooms->mas_rooms = mas_room;
	ft_record_link();

}

static void	ft_create_processed_discovered_parent_mas(void)
{
	int col;
	int *mas_processed;
	int	*mas_parent;
	int *mas_priority;
	int	i;

	col = basic_info_rooms->col_rooms;
	if (!(mas_processed = (int *)malloc(sizeof(int) * col)))
		ft_exit();
	if (!(mas_parent = (int *)malloc(sizeof(int) * col)))
		ft_exit();
	if (!(mas_priority = (int *)malloc(sizeof(int) * col)))
		ft_exit();
	i = 0;
	while (i < col)
	{
		mas_priority[i] = 0;
		mas_parent[i] = -1;
		mas_processed[i++] = -1;
	}
	basic_info_rooms->mas_priority = mas_priority;
	basic_info_rooms->mas_parent = mas_parent;
	basic_info_rooms->mas_processed = mas_processed;
}

void ft_built_int_graph(void)
{
	int		col_room;
	t_room	*room;

	room = basic_info_rooms->room;
	col_room = 0;
	while (room != 0)
	{
		col_room++;
		room = room->next;
	}
	room = basic_info_rooms->room;
	if (col_room == 0)
		ft_exit();
	basic_info_rooms->col_rooms = col_room;
	ft_finish_graph(room, col_room);
	ft_create_processed_discovered_parent_mas();
}

