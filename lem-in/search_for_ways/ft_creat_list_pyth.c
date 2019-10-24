//
// Created by kitos on 16.10.2019.
//

#include "../lem-in.h"

static void	ft_init_pyth(t_pyth *pyth)
{
	pyth->t = 0;
	pyth->number_pyth = 0;
	pyth->pyth = NULL;
	pyth->next = NULL;
	pyth->enext = NULL;
	pyth->next_finish = NULL;
	pyth->hsinif = NULL;
//	pyth->open_room = 0;
}

t_pyth	*ft_insert_pyth(void)
{
	t_pyth	*pyth;
	t_pyth	*copy;
	int 	i;

	if (!(pyth = (t_pyth *)malloc(sizeof(t_pyth))))
		return (NULL);
	ft_init_pyth(pyth);
	copy = group_pyth;
	i = 1;
	if (copy == NULL)
	{
		pyth->number_pyth = i;
		group_pyth = pyth;
		return (pyth);
	}
	while (copy->next != NULL)
	{
		copy = copy->next;
		i++;
	}
	copy->number_pyth = ++i;
	copy->next = pyth;
	return (pyth);
}

void	ft_creat_pyth(t_pyth	*pyth, int name_room)
{
	t_steck	*elem_pyth;
	t_steck	*copy;

	if (!(elem_pyth = (t_steck	*)malloc(sizeof(t_steck))))
		return ;
	elem_pyth->open_room = 0;
	elem_pyth->name_arm = 0;
	elem_pyth->name_room = name_room;
	elem_pyth->next = NULL;
	copy = pyth->pyth;
	if (copy == NULL)
	{
		pyth->pyth = elem_pyth;
		return ;
	}
	while (copy->next)
		copy = copy->next;
	copy->next = elem_pyth;
}