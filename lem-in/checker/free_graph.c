//
// Created by kitos on 14.10.2019.
//

#include "../lem-in.h"

static void ft_clear_links(t_room *room)
{
	t_links_room	*link;
	t_links_room	*copy;

	link = room->links_room;
	if (link == NULL)
		return ;
	if (link->next == NULL)
	{
		free(link);
		room->links_room = NULL;
		return ;
	}
	while (link != NULL)
	{
		copy = link->next;
		free(link->name_str);
		free(link);
		link = copy;
	}
}

static void ft_clear_body_struct_room(t_room *room)
{
	ft_clear_links(room);
	free(room->name_str);
	free(room->coord_x);
	free(room->coord_y);
	room->links_room = NULL;
	room->name_str = NULL;
	room->coord_y = NULL;
	room->coord_x = NULL;
	free(room);
}

static void ft_clear_graph(void)
{
	t_room	*room;
	t_room	*copy;

	room = basic_info_rooms->room;
	free(basic_info_rooms->mas_rooms);
	basic_info_rooms->mas_rooms = NULL;
	while (room != NULL)
	{
		copy = room->next;
		ft_clear_body_struct_room(room);
		room = copy;
	}
	basic_info_rooms->room = NULL;
	free (basic_info_rooms);
	basic_info_rooms = NULL;
}

void ft_exit(void)
{
	ft_putstr("ERROR");
	ft_clear_graph();
	exit (0);
}
