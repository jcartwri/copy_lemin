//
// Created by kitos on 15.10.2019.
//

#include "../lem-in.h"

//int	ft_find_start(void)
//{
//	t_room	*room;
//
//	room = basic_info_rooms->room;
//	while (room != NULL)
//	{
//		if (room->status == 1)
//			return (room->name_int);
//		room = room->next;
//	}
//	return (-1);
//}
//
//int	ft_find_end(void)
//{
//	t_room	*room;
//
//	room = basic_info_rooms->room;
//	while (room != NULL)
//	{
//		if (room->status == 2)
//			return (room->name_int);
//		room = room->next;
//	}
//	return (-1);
//}

void ft_find_first_path(int start, int end, t_pyth *pyth)
{
	if ((start == end) || (end == -1))
	{
		ft_creat_pyth(pyth, start);
//		printf("%i\n", start);
	}
	else
	{
		ft_find_first_path(start, basic_info_rooms->mas_parent[end], pyth);
		ft_creat_pyth(pyth, end);
		if (end != basic_info_rooms->end)
			basic_info_rooms->mas_priority[end]++;
//		printf("%i\n", end);
	}
}

void ft_bfs(void)
{
	t_steck			*elem;
	t_links_room	*p;
	int				start;
	int				v;
	int				y;

	queue_bfs = NULL;
//	if ((start = ft_find_start()) == -1)
//	{
//		//допилить clear
//		ft_exit();
//	}
	start = basic_info_rooms->start;
	enqueue(start);
	basic_info_rooms->mas_processed[start] = 0;
	while (queue_bfs != NULL)
	{
		elem = dequeue();
		v = elem->name_room;
		free(elem);
		basic_info_rooms->mas_processed[v] = 2;
		p = basic_info_rooms->mas_rooms[v]->links_room;
		while (p != NULL)
		{
			y = p->name_int;
//			if ((basic_info_rooms->mas_processed[y] != 1))
//				ft_printf("processed edge (%d, %d) \n", v, y);
			if (basic_info_rooms->mas_processed[y] == -1)
			{
				enqueue(y);
				basic_info_rooms->mas_processed[y] = 0;
				basic_info_rooms->mas_parent[y] = v;
			}
			p = p->next;
		}
//		ft_printf("processed vertex %d\n", v);
	}
	if (basic_info_rooms->mas_parent[basic_info_rooms->end] == -1)
	{
		ft_exit();
	}
	ft_find_first_path(start, basic_info_rooms->end, ft_insert_pyth());
	ft_check_repeat_pyth();
}