//
// Created by kitos on 14.10.2019.
//

#include "../lem-in.h"

static void ft_work_links(t_room *room, char *name)
{
	t_links_room	*new_link;
	t_links_room	*link;

	new_link = ft_create_links(name);
	link = room->links_room;
	if (link == NULL)
	{
		room->links_room = new_link;
		return ;
	}
	while (link->next != NULL)
	{
		if (ft_strcmp(link->name_str, name) == 0)
			return ;
		link = link->next;
	}
	if (ft_strcmp(link->name_str, name) == 0)
		return ;
	link->next = new_link;
}

static void	ft_creat_second_links(char **mas)
{
	t_room	*sec_room;

	sec_room = basic_info_rooms->room;
	while (sec_room != NULL)
	{
		if (ft_strcmp(sec_room->name_str, mas[1]) == 0)
		{
			ft_work_links(sec_room, mas[0]);
			return ;
		}
		sec_room = sec_room->next;
	}
}

static void ft_record_links_room(int *flag, char **mas)
{
	t_room	*room;

	room = basic_info_rooms->room;
	if (room == NULL)
	{
		*flag = -1;
		return ;
	}
	while (room != NULL)
	{
		if (ft_strcmp(room->name_str, mas[0]) == 0)
		{
			ft_work_links(room, mas[1]);
			ft_creat_second_links(mas);
			return ;
		}
		room = room->next;
	}
	*flag = -1;
}

static int	ft_flag_two_or_three(char *line, int *flag)
{
	int i;
	int col;

	if (*flag == 3)
		return (1);
	i = 0;
	col = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ' ')
			col++;
		i++;
	}
	if (col != 2)
	{
		*flag = 3;
//		*flag = -1;
//		return (-1);
	}
	return (1);
}

void ft_record_link_rooms(char *line, int *key, int *flag)
{
	char	**mas;
	int 	i;

	i = -1;
	if (ft_flag_two_or_three(line, flag) == -1)
		return ;
	if (*flag == 2)
	{
		ft_record_coord_rooms(line, key, flag);
		return ;
	}
	mas = ft_strsplit(line, '-');
	while (mas[++i])
	{
		if ((i + 1) > 2)
		{
			*flag = -1;
			ft_strdel_mas_mas(mas);
			free(mas);
			return ;
		}
	}
	ft_record_links_room(flag, mas);
	ft_strdel_mas_mas(mas);
	free(mas);
}