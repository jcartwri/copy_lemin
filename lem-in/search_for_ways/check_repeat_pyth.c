//
// Created by kitos on 16.10.2019.
//

#include "../lem-in.h"

static void	ft_clean_room(t_pyth *pyth)
{
	t_steck	*elem;
	t_steck	*copy_elem;

	elem = pyth->pyth;
	while (elem->next != NULL)
	{
		copy_elem = elem;
		elem = elem->next;
		if (elem->next == NULL)
		{
			basic_info_rooms->mas_priority[elem->name_room] += 4;
			free(elem);
			copy_elem->next = NULL;
			elem = pyth->pyth;
		}
	}
	basic_info_rooms->mas_priority[elem->name_room] += 4;
	free(elem);
	pyth->pyth = NULL;
}

static void	ft_clean_pyth()
{
	t_pyth *elem;
	t_pyth *copy_elem;

	elem = group_pyth;
	while (elem->next != NULL)
	{
		copy_elem = elem;
		elem = elem->next;
		if (elem->next == NULL)
		{
			copy_elem->next = NULL;
			ft_clean_room(elem);
			return ;
		}
	}
}

static int	ft_check_repeat_room(t_pyth	*copy_pyth, t_pyth	*pyth)
{
	t_steck	*elem;
	t_steck	*copy_elem;

	elem = pyth->pyth;
	copy_elem = copy_pyth->pyth;
	while (elem != NULL || copy_elem != NULL)
	{
		if (elem->name_room == copy_elem->name_room)
		{
			elem = elem->next;
			copy_elem = copy_elem->next;
		}
		else
			return (0);
	}
	return (1);
}

void	ft_check_repeat_pyth()
{
	t_pyth	*pyth;
	t_pyth	*copy_pyth;

	pyth = group_pyth;
	if (pyth == NULL || pyth->next == NULL)
		return ;
	while (pyth->next != NULL)
		pyth = pyth->next;
	copy_pyth = group_pyth;
	while (copy_pyth != pyth)
	{
		if (ft_check_repeat_room(copy_pyth, pyth) == 1)
		{
			ft_clean_pyth();
			free(pyth);
			return ;
		}
		copy_pyth = copy_pyth->next;
	}
}