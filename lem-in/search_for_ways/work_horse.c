//
// Created by kitos on 16.10.2019.
//

#include "../lem-in.h"

t_pyth	*ft_insert_antijoin_pyth(t_pyth	*antijoin_pyth, t_pyth	*pyth)
{
	t_pyth	*elem;

	if (antijoin_pyth == NULL)
	{
		pyth->enext = NULL;
		return (pyth);
	}
	elem = antijoin_pyth;
	while (elem->enext != NULL)
		elem = elem->enext;
	elem->enext = pyth;
	pyth->enext = NULL;
	return (antijoin_pyth);
}

static int	ft_match_two_pyth(t_pyth *elem, t_pyth *copy)
{
	t_steck	*room_elem;
	t_steck	*room_copy;
	int 	flag;

	flag = 0;
	if (elem == copy)
		return (-1);
	room_elem = elem->pyth;
	while (room_elem->next != NULL)
	{
		room_copy = copy->pyth;
		while (room_copy->next != NULL)
		{
			if ((room_elem->name_room != basic_info_rooms->start) && (room_elem->name_room == room_copy->name_room))
			{
				flag = 1;
				break ;
			}
			room_copy = room_copy->next;
		}
		if (flag == 1)
			break ;
		room_elem = room_elem->next;
	}
	if (flag == 1)
		return (-1);
	return (0);
}

t_pyth	*ft_find_antijoin_pyth(t_pyth *pyth)
{
	t_pyth	*antijoin_pyth;
	t_pyth	*elem;
	int 	flag;

	antijoin_pyth = NULL;
	elem = group_pyth;
	while (elem != NULL)
	{
		if (elem != pyth)
		{
			flag = ft_match_two_pyth(pyth, elem);
			if (flag == 0)
				antijoin_pyth = ft_insert_antijoin_pyth(antijoin_pyth, elem);
		}
		elem = elem->next;
	}
	return (antijoin_pyth);
}

static int 	ft_lets_check_pyth(t_pyth *f_pyth)
{
	int	i;
	t_pyth	*elem;
	t_pyth	*copy;

	i = 0;
	elem = f_pyth;
	while (elem != NULL)
	{
		i++;
		elem = elem->next_finish;
	}
	if (i == 1)
		return (1);
	elem = f_pyth;
	while (elem != NULL)
	{
		copy = f_pyth;
		if (copy != elem)
		{
			if (ft_match_two_pyth(elem, copy) == -1)
				return (-1);
		}
		elem = elem->next_finish;
	}
	return (1);
}

void	ft_test_finish(t_pyth *f_pyth)
{
	int 	col_pyth;
	int 	length_pyth;
	int 	t;
	t_pyth	*pyth;

	if (ft_lets_check_pyth(f_pyth) == -1)
		return ;
	pyth = f_pyth;
	col_pyth = 0;
	length_pyth = 0;
	while (pyth != NULL)
	{
		col_pyth++;
		length_pyth += pyth->number_pyth - 1;
		pyth = pyth->hsinif;
	}
	t = basic_info_rooms->numbers_of_arms + length_pyth;
	if (t % col_pyth == 0)
		t = t / col_pyth - 1;
	else
		t = t / col_pyth;
	if ((finish_pyth != NULL) && (t >= finish_pyth->t))
		return ;
	pyth = f_pyth;
	finish_pyth = f_pyth;
	f_pyth->t = t;
	while (pyth != NULL)
	{
		pyth = pyth->hsinif;
		f_pyth->next_finish = pyth;
		f_pyth = pyth;
	}
}

static void	ft_join_hsinif_room(t_pyth *pyth, t_pyth *elem)
{
	if (pyth == NULL)
		return ;
	while (pyth->hsinif != NULL)
		pyth = pyth->hsinif;
	pyth->hsinif = elem;
	elem->hsinif = NULL;
}

void ft_check_set_pyths(t_pyth *pyth, t_pyth *antijoin)
{
	t_pyth	*f_pyth;
	t_pyth	*elem;
	t_pyth	*copy;
	int 	i;

	pyth->hsinif = NULL;
	ft_test_finish(pyth);
	elem = antijoin;
	while (elem != NULL)
	{
		i = 1;
		f_pyth = pyth;
		pyth->hsinif = NULL;
		ft_join_hsinif_room(f_pyth, elem);
		ft_test_finish(f_pyth);
		copy = elem->enext;
		while (copy != NULL)
		{
			if (++i > 21)
			  break ;
			ft_join_hsinif_room(f_pyth, copy);
			ft_test_finish(f_pyth);
			copy = copy->enext;
		}
		elem = elem->enext;
	}
}

void ft_find_combiation_pyth()
{
	t_pyth	*pyth;
	t_pyth	*antijoin_pyth;

	pyth = group_pyth;
	while (pyth != NULL)
	{
		antijoin_pyth = ft_find_antijoin_pyth(pyth);
		ft_check_set_pyths(pyth, antijoin_pyth);
		pyth = pyth->next;
	}
}

void	ft_find_many_pyth()
{
	int col;
	int i;
	int y;
	int len_mas;

	i = 0;
	if (basic_info_rooms->col_rooms > basic_info_rooms->numbers_of_arms)
		col = basic_info_rooms->numbers_of_arms * 2;
	else
		col = basic_info_rooms->col_rooms * 2;
	len_mas = basic_info_rooms->col_rooms;
	while (i < col)
	{
		y = -1;
		while (++y < len_mas)
		{
			basic_info_rooms->mas_parent[y] = -1;
			basic_info_rooms->mas_processed[y] = -1;
		}
		ft_bfs();
		i++;
	}
}

void	ft_find_start_end()
{
	t_room	*room;

	room = basic_info_rooms->room;
	while (room != NULL)
	{
		if (room->status == 1)
			basic_info_rooms->start = room->name_int;
		else if (room->status == 2)
			basic_info_rooms->end = room->name_int;
		room = room->next;
	}
}

void ft_settings_pyth(void)
{
	t_steck	*elem;
	t_pyth	*pyth;
	int 	col;

	pyth = group_pyth;
	while (pyth != NULL)
	{
		col = 0;
		elem = pyth->pyth;
		while (elem != NULL)
		{
			col++;
			elem = elem->next;
		}
		pyth->number_pyth = col;
		pyth = pyth->next;
	}
}

static void ft_output_arm(int arm, int i)
{
	ft_putchar('L');
	ft_putstr(ft_itoa(arm));
	ft_putchar('-');
	ft_putstr(basic_info_rooms->mas_rooms[i]->name_str);
	ft_putchar(' ');
}

//static int ft_output_begin_arms(int x, int arm, int *a)
//{
//	t_finish_pyth	*copy;
//	int 			i;
//	int 			b;
//
//	b = 0;
//	copy = end->finish[x];
//	i = copy->col_room - 2;
//	while (i > 0)
//	{
//		if (copy->pyth[i]->open_room == 1)
//		{
//			b = 1;
//			ft_output_arm(copy->pyth[i]->name_arm, copy->pyth[i + 1]->name_room, a);
//			copy->pyth[i]->open_room = 0;
//			copy->pyth[i + 1]->name_arm = copy->pyth[i]->name_arm;
//			copy->pyth[i + 1]->open_room = 1;
//		}
//		i--;
//	}
//	if (arm > 0)
//	{
//		b = 1;
//		end->finish[x]->pyth[1]->name_arm = arm;
//		end->finish[x]->pyth[1]->open_room = 1;
//		ft_output_arm(end->finish[x]->pyth[1]->name_arm, end->finish[x]->pyth[1]->name_room, a);
//	}
//	if (b == 0)
//		return (-1);
//	return (1);
//}

static int *ft_creat_mas_arms_pyth()
{
	int	*mas;
	int i;
	int flag;
	int N;

	i = -1;
	if ((end->N + end->L) % end->k == 0)
		flag = 0;
	else
		flag = 1;
  	N = end->N - flag;
	mas = (int *)malloc(sizeof(int) * end->k);
	while (end->finish[++i])
	{
		mas[i] = (N + end->L) / end->k - (end->finish[i]->col_room - 1);
	}
		return (mas);
}

//static int ft_check_empty_mas(int *mas, int *flag)
//{
//	int				i;
//	int				x;
//	t_finish_pyth	*copy;
//
//	i = 0;
////	if (*flag == 1 && )
////	{
////		*flag = 0;
////		return (2);
////	}
//	while (i < end->k)
//	{
//	  	if (mas[i] > 0)
//			return (1);
//	  	i++;
//	}
//	x = -1;
//	while (end->finish[++x])
//	{
//	  	copy = end->finish[x];
//	  	i = copy->col_room - 2;
//	  	while (i > 0)
//	  	{
//			if (copy->pyth[i]->open_room == 1)
//		  		return (1);
//			i--;
//	  	}
//	}
//  	return (0);
//}

static void	ft_check_push_arms(int i, int *mas)
{
	if (mas[i] > 0)
	{
		end->finish[i]->pyth[1]->open_room = 1;
		end->finish[i]->pyth[1]->name_arm = out_put_name_arm + 1;
		ft_output_arm(out_put_name_arm + 1, end->finish[i]->pyth[1]->name_room);
		out_put_name_arm++;
		mas[i]--;
	}
}

static void ft_push(int f, int p, int name_arm)
{
	end->finish[f]->pyth[p]->open_room = 1;
	end->finish[f]->pyth[p]->name_arm = name_arm;
	ft_output_arm(name_arm, end->finish[f]->pyth[p]->name_room);
}

static int ft_check_push_first_arm(int *mas, int *flag)
{
	int i;

	if (out_put_name_arm == 0)
	{
		i = -1;
		while (end->finish[++i] != NULL)
		{
			if (mas[i] > 0)
			{
//				ft_push(i, 1, out_put_name_arm + 1);
				end->finish[i]->pyth[1]->open_room = 1;
				end->finish[i]->pyth[1]->name_arm = out_put_name_arm + 1;
				ft_output_arm(out_put_name_arm + 1, end->finish[0]->pyth[1]->name_room);
				out_put_name_arm++;
				mas[i]--;
			}
		}
		return (1);
	}
	else if (*flag == 1 && end->finish[0]->pyth[0]->open_room == 0)
	{
		*flag = 0;
		ft_push(0, 0, out_put_name_arm + 1);
		out_put_name_arm++;
		return (1);
	}
	return (0);
}

//static void ft_census(t_finish_pyth *copy, int j)
//{
//	ft_output_arm(copy->pyth[j]->name_arm, copy->pyth[j + 1]->name_room);
//	copy->pyth[j]->open_room = 0;
//	copy->pyth[j + 1]->name_arm = copy->pyth[j]->name_arm;
//	copy->pyth[j + 1]->open_room = 1;
//}

static void ft_output_begin_arms(int *mas, int *flag)
{
	int				i;
	int 			j;
	t_finish_pyth	*copy;

	if (ft_check_push_first_arm(mas, flag) ==  1)
		return ;
	i = -1;
	while (++i < end->k)
	{
		copy = end->finish[i];
		j = copy->col_room - 2;
//		if (j == 0)
//		{
//			copy->pyth[0]->
//			continue ;
//		}
		while (j > 0)
		{
			if (copy->pyth[j]->open_room == 1)
			{
				ft_output_arm(copy->pyth[j]->name_arm, copy->pyth[j + 1]->name_room);
				copy->pyth[j]->open_room = 0;
				copy->pyth[j + 1]->name_arm = copy->pyth[j]->name_arm;
				copy->pyth[j + 1]->open_room = 1;
			}
//			else if (j == 1 && copy->pyth[j]->open_room == 1)
//			{
////				ft_census(copy, j);
//				ft_output_arm(copy->pyth[j]->name_arm, copy->pyth[j + 1]->name_room);
//				copy->pyth[j]->open_room = 0;
//				copy->pyth[j + 1]->name_arm = copy->pyth[j]->name_arm;
//				copy->pyth[j + 1]->open_room = 1;
//				ft_check_push_arms(i, mas);
//			}
			ft_check_push_arms(i, mas);
			j--;
		}
	}
}

void	ft_output_res(void)
{
  	int flag;
  	int *mas;
  	int i;

  	if ((end->N + end->L) % end->k == 0)
  	  	flag = 0;
  	else
  	  	flag = 1;
	mas = ft_creat_mas_arms_pyth();
	i = -1;
	out_put_name_arm = 0;
	while (++i < end->t)
	{
		ft_output_begin_arms(mas, &flag);
		ft_putchar('\n');
	}
}

//void	ft_output_res(void)
//{
//	int t;
//	int i;
//	int arm;
//	int a;
//
//	t = -1;
//	arm = 0;
//	while (++t < end->t - 1)
//	{
//		i = -1;
//		a = 1;
//		while (end->finish[++i] != NULL)
//		{
//			if ((arm != -1) && (arm < end->N))
//				arm++;
//			else
//				arm = -1;
//			if (ft_output_begin_arms(i, arm, &a) == -1)
//				return ;
//		}
//		ft_putchar('\n');
//	}
//}

void	ft_work_horse(void)
{
	group_pyth = NULL;
	ft_find_start_end();
	ft_bfs();
	ft_find_many_pyth();
	finish_pyth = NULL;
	ft_settings_pyth();
	ft_find_combiation_pyth();
	end = NULL;
	ft_creat_end_and_finish_pyth();
	ft_output_res();
	ft_clean_all_memory();
}