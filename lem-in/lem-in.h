#ifndef LEM_IN_LEM_IN_H
#define LEM_IN_LEM_IN_H

# include <stdio.h>
//# include "lib/printf/ft_printf.h"
# include "lib/printf/libft/libft.h"
# include "lib/printf/libft/get_next_line.h"

typedef struct			s_room
{
	int					status;
	char				*name_str;
	int					name_int;
	char				*coord_x;
	char				*coord_y;
	int 				col_links;
	int 				*mas_links;
//        int		len;
	struct s_links_room	*links_room;
	struct s_room		*next;
}						t_room;

typedef struct			s_links_room
{
	char				*name_str;
	int 				name_int;
	struct s_links_room	*next;

}						t_links_room;

typedef struct			s_info_rooms
{
	int					numbers_of_arms;
	int 				start;
	int 				end;
	int 				col_rooms;
	t_room				**mas_rooms;
	t_room				*room;
	int 				*mas_processed;
	int 				*mas_parent;
	int 				*mas_priority;
}						t_info_rooms;

typedef struct			s_steck
{
	int 				open_room;
	int 				name_arm;
	int					name_room;
	struct s_steck		*next;
}						t_steck;

typedef struct			s_pyth
{
	int 				t;

	int 				number_pyth;
	t_steck				*pyth;
	struct s_pyth		*next;
	struct s_pyth		*enext;
	struct s_pyth		*hsinif;
	struct s_pyth		*next_finish;
}						t_pyth;

typedef struct			s_finish_pyth
{
	int 				col_room;
	t_steck				**pyth;
	struct	s_finish_pyth	*next;
}						t_finish_pyth;

typedef struct			s_end
{
	int 				L;
	int 				k;
	int 				N;
	int 				t;
	t_finish_pyth		**finish;
}						t_end;

t_info_rooms			*basic_info_rooms;
t_steck					*queue_bfs;
t_pyth					*group_pyth;
t_pyth					*finish_pyth;
t_end					*end;
int 					out_put_name_arm;

int						main(void);
// checker
void					ft_checker(void);
t_room					*ft_creat_room(void);
t_info_rooms			*ft_creat_info_rooms(int col_arms);
void					ft_strdel_mas_mas(char **mas);
t_links_room			*ft_create_links(char *str);
void					ft_exit(void);
void					ft_record_coord_rooms(char *line, int *key, int *flag);
void					ft_record_link_rooms(char *line, int *key, int *flag);
void					ft_sum_flags(int *flag, int *key);
void					ft_works_arms(int *key, int *flag, char *line);
void					ft_built_int_graph(void);
void					ft_built_int_mas_links(void);
//
//bfs
t_steck					*ft_creat_steck(int name_room);
t_steck					*dequeue(void);
void					enqueue(int name_room);
void					ft_bfs(void);
void					ft_creat_pyth(t_pyth	*pyth, int name_room);
t_pyth					*ft_insert_pyth(void);
void					ft_check_repeat_pyth();
void					ft_work_horse(void);
void					ft_creat_end_and_finish_pyth(void);
void					ft_clean_all_memory(void);

#endif

// инструкция
//
//basic_info_rooms->mas_processed[] имеет три состояния:]
//	1) -1 - не открыт
//	2)  0 - открыт
//	3)	1 - считаны все смежности или соседи
//
//room->status имеет три состояния
//	1) 0 - простая комната
//	2) 1 - start
//	3) 2 - end
//
//basic_info_rooms->mas_parent[] - имеет два состояния
//	1) -1 - не определен родитель
//	2) номер родителя в mas