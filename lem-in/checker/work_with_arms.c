//
// Created by kitos on 14.10.2019.
//

#include "../lem-in.h"


void ft_works_arms(int *key, int *flag, char *line)
{
	int	col;
	int	i;

	i = -1;
	col = ft_atoi(line);
	while (line && line[++i])
	{
		if (!(line[i] >= '0' && line[i] <= '9'))
		{
			*flag = -1;
			return ;
		}
	}
	if (col == 0 && line && line[0] != '0')
	{
		*flag = -1;
		return ;
	}
	basic_info_rooms = ft_creat_info_rooms(col);
	*key = 0;
}

void ft_sum_flags(int *flag, int *key)
{
	*key = *key + 1;
	*flag = *flag + 1;
}
