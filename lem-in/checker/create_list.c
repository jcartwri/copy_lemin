//
// Created by kitos on 13.10.2019.
//

#include "../lem-in.h"

t_links_room	*ft_create_links(char *str)
{
	t_links_room	*link;

	if ((link = (t_links_room*)malloc(sizeof(t_links_room))) == NULL)
		return (NULL);
	link->name_str = ft_strdup(str);
	link->name_int = -1;
	link->next = NULL;
	return (link);
}


t_room	*ft_creat_room(void)
{
	t_room	*room;

	if ((room = (t_room *)malloc(sizeof(t_room))) == NULL)
		return (NULL);
	room->status = 0;
	room->name_str = NULL;
	room->name_int = -1;
	room->coord_x = NULL;
	room->coord_y = NULL;
	room->links_room = NULL;
	room->next = NULL;
	return (room);
}

t_info_rooms* ft_creat_info_rooms(int col_arms)
{
	t_info_rooms*	info;

	if ((info = (t_info_rooms *)malloc(sizeof(t_room))) == NULL)
		return (NULL);
	info->room = NULL;
	info->numbers_of_arms = col_arms;
	return (info);
}

void	ft_strdel_mas_mas(char **mas)
{
	int	i;

	i = -1;
	while (mas[++i])
	{
		ft_strdel(&mas[i]);
	}
}