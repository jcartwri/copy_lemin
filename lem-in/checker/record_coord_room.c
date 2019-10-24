//
// Created by kitos on 14.10.2019.
//

#include "../lem-in.h"

static int ft_check_str_on_digit(char *str)
{
	int i;

	i = -1;
	while (str && str[++i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (-1);
	}
	return (1);
}

static void	ft_record_room_in_info(int *key, int *flag, char **mas)
{
	t_room	*room;
	t_room	*new_room;

	new_room = ft_creat_room();
	new_room->name_str = ft_strdup(mas[0]);
	new_room->coord_x = ft_strdup(mas[1]);
	new_room->coord_y = ft_strdup(mas[2]);
	new_room->next = NULL;
	if (*key == 1)
	{
		if (*flag == 0 || *flag == 1)
			new_room->status = 1;
		if (*flag == 2)
			new_room->status = 2;
		*key = 0;
	}
	if (basic_info_rooms->room == NULL)
	{
		basic_info_rooms->room = new_room;
		return ;
	}
	room = basic_info_rooms->room;
	while (room->next != NULL)
		room = room->next;
	room->next = new_room;
}

static int ft_check_space(char *line, int *flag)
{
	int i;
	int col;

	i = -1;
	if (line == NULL)
	{
		*flag = -1;
		return (-1);
	}
	col = 0;
	while (line[++i] != '\0')
	{
		if (line[i] == ' ')
			col++;
	}
	if (col != 2)
	{
		*flag = -1;
		return (-1);
	}
	return (1);
}

void ft_record_coord_rooms(char *line, int *key, int *flag)
{
	char	**mas;
	int 	i;

	i = -1;
	if (ft_check_space(line, flag) == -1)
		return ;
	mas = ft_strsplit(line, ' ');
	while (mas[++i])
	{
		if ((i != 0 && ft_check_str_on_digit(mas[i]) == -1) || (i + 1) > 3)
		{
			*flag = -1;
			ft_strdel_mas_mas(mas);
			free(mas);
			return ;
		}
	}
	ft_record_room_in_info(key, flag, mas);
	ft_strdel_mas_mas(mas);
	free(mas);
}