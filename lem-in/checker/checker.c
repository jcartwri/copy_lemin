//
// Created by kitos on 13.10.2019.
//

// удалить
#include <fcntl.h>
//
# include "../lem-in.h"

void ft_check_graph(void)
{
	t_room	*room;

	room = basic_info_rooms->room;
	if (basic_info_rooms->numbers_of_arms < 0)
		ft_exit();
	while (room != NULL)
	{
		if 	(ft_atoi(room->coord_x) < 0 || ft_atoi(room->coord_y) < 0)
			ft_exit();
		else if (!room->name_str || (room->name_str && room->name_str[0] == 'L'))
			ft_exit();
		room = room->next;
	}
}

void ft_built_graph(void)
{
	char    *line;
	int     flag;
	int     key;

	flag = 0;
	key = -1;
	//###########
	int fd;

	fd = open("../card", O_RDWR);
	//############
	while (get_next_line(fd, &line) == 1)
	{
		ft_putendl(line);
		if (key == -1)
			ft_works_arms(&key, &flag, line);
		else if (ft_strcmp(line, "##start") == 0 && flag == 0)
			ft_sum_flags(&flag, &key);
		else if (ft_strcmp(line, "##end") == 0 && flag == 1)
			ft_sum_flags(&flag, &key);
		else if ((flag == 0 || flag == 1) && line && line[0] != '#')
			ft_record_coord_rooms(line, &key, &flag);
		else if ((flag == 2 || flag == 3) && line && line[0] != '#')
			ft_record_link_rooms(line, &key, &flag);
		else if (line[0] == '#')
		  continue ;
		else
		  ft_exit ();
	  	if (flag == -1)
	  	  ft_exit();
	}
	ft_putchar('\n');
}

void ft_checker(void)
{
	ft_built_graph();
	ft_check_graph();
	ft_built_int_graph();
	ft_built_int_mas_links();
}



