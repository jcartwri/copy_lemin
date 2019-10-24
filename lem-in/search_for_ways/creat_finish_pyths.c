//
// Created by kitos on 17.10.2019.
//

#include "../lem-in.h"

static void	ft_creat_int_mas_pyth(t_finish_pyth	*pyth, t_pyth	*elem)
{
	t_steck	*copy;
	int 	i;
	int 	col;

	i = 0;
	copy = elem->pyth;
	col = pyth->col_room;
	end->L += col - 1;
	pyth->pyth = (t_steck **)malloc(sizeof(t_steck *) * (col + 1));
	pyth->pyth[col] = NULL;
	while (copy != NULL)
	{
		pyth->pyth[i++] = copy;
		copy = copy->next;
	}
}

static t_finish_pyth	*ft_create_t_finish_pyth(t_pyth	*elem)
{
	t_finish_pyth	*pyth;
	t_steck			*copy;
	int 			col_room;

	col_room = 0;
	if (!(pyth = (t_finish_pyth *)malloc(sizeof(t_finish_pyth))))
		return	(NULL);
	pyth->next = NULL;
	copy = elem->pyth;
	while (copy != NULL)
	{
		col_room++;
		copy = copy->next;
	}
	pyth->col_room = col_room;
	ft_creat_int_mas_pyth(pyth, elem);
	pyth->next = NULL;
	return (pyth);
}

static t_finish_pyth	**mas_mas_finish_pyth(t_finish_pyth *finish)
{
	t_finish_pyth	*copy;
	t_finish_pyth	**mas_mas;
	int 			i;

	i = 0;
	copy = finish;
	while (copy != NULL)
	{
		i++;
		copy = copy->next;
	}
	end->k = i;
	mas_mas = (t_finish_pyth **)malloc(sizeof(t_finish_pyth *) * (i + 1));
	mas_mas[i] = NULL;
	copy = finish;
	i = 0;
	while (copy != NULL)
	{
		mas_mas[i++] = copy;
		copy = copy->next;
	}
	return (mas_mas);
}


void	ft_creat_end_and_finish_pyth(void)
{
	t_finish_pyth	*finish;
	t_finish_pyth	*copy;
	t_pyth			*elem;

	end = (t_end *)malloc(sizeof(t_end));
	end->t = 0;
	end->k = 0;
	end->L = 0;
	end->N = basic_info_rooms->numbers_of_arms;
	elem = finish_pyth;
	finish = ft_create_t_finish_pyth(elem);
	copy = finish;
	while (elem->next_finish != NULL)
	{
		elem = elem->next_finish;
		copy->next = ft_create_t_finish_pyth(elem);
		copy = copy->next;
	}
	copy->next = NULL;
	end->finish = mas_mas_finish_pyth(finish);
	end->t = end->N + end->L;
	if ((end->t % end->k) == 0)
		end->t = end->t / end->k - 1;
	else
		end->t = end->t / end->k;
}