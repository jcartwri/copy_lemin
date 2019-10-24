//
// Created by kitos on 15.10.2019.
//

#include "../lem-in.h"

t_steck	*ft_creat_steck(int name_room)
{
	t_steck	*steck;

	if (!(steck = (t_steck *)malloc(sizeof(t_steck))))
		return (NULL);
	steck->name_room = name_room;
	steck->next = NULL;
	return (steck);
}

t_steck	*dequeue(void)
{
	t_steck	*elem;
	t_steck	*copy;

	if (queue_bfs == NULL)
		return (NULL);
	elem = queue_bfs;
	if (elem->next == NULL)
	{
		queue_bfs = NULL;
		return (elem);
	}
	while (elem->next != NULL)
	{
		if (elem->next->next == NULL)
		{
			copy = elem->next;
			elem->next = NULL;
			return (copy);
		}
		elem = elem->next;
	}
	return (NULL);
}

void	enqueue(int name_room)
{
	t_steck	*elem;
	t_steck	*copy1;
	t_steck	*copy2;

	elem = ft_creat_steck(name_room);
	if (queue_bfs == NULL)
	{
		queue_bfs = elem;
		return ;
	}
	copy1 = queue_bfs;
	if (basic_info_rooms->mas_priority[name_room] >= basic_info_rooms->mas_priority[copy1->name_room])
	{
		elem->next = copy1;
		queue_bfs = elem;
		return ;
	}
	while (basic_info_rooms->mas_priority[name_room] < basic_info_rooms->mas_priority[copy1->name_room])
	{
		if (copy1->next == NULL)
		{
			copy1->next = elem;
			return ;
		}
		copy2 = copy1;
		copy1 = copy1->next;
	}
	copy2->next = elem;
	elem->next = copy1;
}