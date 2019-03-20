/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 17:40:41 by bsprigga          #+#    #+#             */
/*   Updated: 2019/03/20 19:12:40 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
void	check_coordinates(void)
{
 	t_room		*start_of_list;
 	t_room		*tmp;

 	if (!g_params)
 		return ;
 	start_of_list = g_params->start_of_list;
 	while (start_of_list)
 	{
 		tmp = start_of_list->next;
 		while (tmp)
 		{
 			if (tmp->coord_x == start_of_list->coord_x &&
 				tmp->coord_y == start_of_list->coord_y)
 				error_exit();
 			tmp = tmp->next;
 		}
		start_of_list = start_of_list->next;
	}
}
*/

int		num_of_nghbrs(t_neighbour *neighbour)
{
	int		i;

	i = 0;
	while (neighbour)
	{
		neighbour = neighbour->next;
		i++;
	}
	return (i);
}

int		sum_of_paths(t_path **paths, int flows)
{
	int		sum;
	int		i;

	i = 0;
	sum = 0;
	while (i < flows)
	{
		sum += paths[i]->len_seq;
		i++;
	}
	return (sum);
}

int		ft_min(int a, int b, int c)
{
	if (a <= b && a <= c)
		return (a);
	if (b <= a && b <= c)
		return (b);
	return (c);
}

t_room	**lst_to_array(t_neighbour *nghbr, int len)
{
	int		i;
	t_room	**res;

	res = (t_room **)malloc(sizeof(*res) * len);
	i = 0;
	while (nghbr)
	{
		res[i] = nghbr->room;
		nghbr = nghbr->next;
		i++;
	}
	return (res);
}

// void	first_iter_ants_move(int *nr_steps)
// {
// 	t_path	*tmp;
// 	int		space_flag;

// 	space_flag = 0;
// 	nr_steps--;
// 	tmp = g_params->start_of_list_of_paths;
// 	while (tmp)
// 	{
// 		tmp->seq->room->ant_nr = g_params->nr_ants;
// 		if (space_flag)
// 			write(1, " ", 1);
// 		else
// 			space_flag = 1;
// 		ft_printf("L%i-%s", g_params->nr_ants, tmp->seq->room->name);
// 		g_params->nr_ants--;
// 		tmp = tmp->next;
// 	}
// 	write(1, "\n", 1);
// }

void	new_ants_move_in_path(int i, t_room *room, int *space_flag,
								int **nr_ants_to_move_in_paths)
{
	if ((*nr_ants_to_move_in_paths)[i] > 0 && g_params->nr_ants > 0)
	{
		room->ant_nr = g_params->nr_ants;
		g_params->nr_ants--;
		if (*space_flag)
			write(1, " ", 1);
		else
			*space_flag = 1;
		ft_printf("L%i-%s", room->ant_nr, room->name);
		(*nr_ants_to_move_in_paths)[i]--;
	}
}

void	print_existing_ants_movement(t_room **room, int *space_flag) //t_room *prev_iter_room, 
{
	if ((*room)->next_elem == g_params->end && (*room)->ant_nr)
	{
		if (*space_flag)
			write(1, " ", 1);
		else
			*space_flag = 1;
		ft_printf("L%i-%s", (*room)->ant_nr, (*room)->next_elem->name);
		(*room)->ant_nr = 0;
	}
	// else
		while ((*room)->prev_path != g_params->start && (*room)->prev_path->ant_nr)
		{
			// if ((*room)->ant_nr) //&& tmp->seq->next->room != g_params->end
			// {
			(*room)->ant_nr = (*room)->prev_path->ant_nr;
			(*room)->prev_path->ant_nr = 0;
			if (*space_flag)
				write(1, " ", 1);
			else
				*space_flag = 1;
			ft_printf("L%i-%s", (*room)->ant_nr, (*room)->name);
			// }
			(*room) = (*room)->prev_path;
		}

}

void	iter_ants_move(int nr_steps, t_room **room_arr,
						int *nr_ants_to_move_in_paths, int cnt_paths)
{
	t_room		*tmp_room;
	int			i;
	int			space_flag;


	while (nr_steps--)
	{
		space_flag = 0;
		i = 0;
		while (i < cnt_paths)
		{
			// if (room_arr[i] == g_params->end)
			// {
			// 	print_existing_ants_movement(&(room_arr[i]), tmp_room, &space_flag);
			// 	//tmp_room = room_arr[i];
			// }
			// else
			// {
			tmp_room = room_arr[i];
			print_existing_ants_movement(&tmp_room, &space_flag);
			// }
			// while (tmp_room->prev_path != g_params->start)
			// {
			// 	if (tmp_room->ant_nr) //&& tmp->seq->next->room != g_params->end
			// 	{
			// 		tmp_room->next->ant_nr = tmp_room->ant_nr;
			// 		if (space_flag)
			// 			write(1, " ", 1);
			// 		else
			// 			space_flag = 1;
			// 		ft_printf("L%i-%s", tmp_room->ant_nr, tmp_room->name);
			// 		tmp_room->ant_nr = 0;
			// 	}
			// 	tmp_room = tmp_room->prev_path;
			// }
			new_ants_move_in_path(i, tmp_room, &space_flag, &nr_ants_to_move_in_paths);
			if (room_arr[i]->next_elem != g_params->end)
				room_arr[i] = room_arr[i]->next_elem;
			i++;
		}
		write(1, "\n", 1);
	}
	// ft_printf("%i\n", g_params->nr_ants);
}

void	rooms_arr_setup(t_room ***room_arr, int **nr_ants_to_move_in_paths,
						int cnt_paths, int sum_paths)
{
	t_path		*tmp;
	int			i;

	if (!(*room_arr = (t_room **)malloc(sizeof(t_room *) * cnt_paths)))
		exit(0);
	if (!(*nr_ants_to_move_in_paths = (int *)malloc(sizeof(int) * cnt_paths)))
		exit(0);
	i = 0;
	tmp = g_params->start_of_list_of_paths;
	while (tmp)
	{
		(*nr_ants_to_move_in_paths)[i] = (g_params->nr_ants + sum_paths)
									/ cnt_paths - tmp->len_seq + ((g_params->nr_ants + sum_paths) / cnt_paths != 0);
		// ft_printf("i = %i num ants = %i\n", i, (*nr_ants_to_move_in_paths)[i]);
		(*room_arr)[i] = tmp->seq->room;
		tmp = tmp->next;
		++i;
	}
}

void	print_paths(int nr_steps)
{
	t_path		*tmp;
	int			sum_paths;
	int			cnt_paths;
	t_room		**room_arr;
	int			*nr_ants_to_move_in_paths;

	sum_paths = 0;
	cnt_paths = 0;
	tmp = g_params->start_of_list_of_paths;
	while (tmp)
	{
		sum_paths += tmp->len_seq;
		cnt_paths++;
		tmp = tmp->next;
	}
	rooms_arr_setup(&room_arr, &nr_ants_to_move_in_paths, cnt_paths, sum_paths);
	// tmp = g_params->start_of_list_of_paths;
	// while (tmp)
	// {
	// 	tmp->nr_ants_to_move = (g_params->nr_ants + sum_paths)
	// 							/ cnt_paths - tmp->len_seq;
	// 	tmp = tmp->next;
	// }
	
	iter_ants_move(nr_steps, room_arr, nr_ants_to_move_in_paths, cnt_paths);
	
	// first_iter_ants_move(&nr_steps);
	// while (nr_steps--)
	// {
	// 	tmp = g_params->start_of_list_of_paths;
	// 	while (tmp)
	// 	{
	// 		tmp_seq = tmp->seq;
	// 		if (tmp_seq->room->ant_nr) //&& tmp->seq->next->room != g_params->end
	// 		{
	// 			tmp_seq->next->room->ant_nr = tmp_seq->room->ant_nr;

	// 		}
	// 		tmp = tmp->next;
	// 	}
	// }
}

void	print_paths_(void)
{
	int				i;
	t_neighbour		*seq;
	t_path			*paths;

	paths = g_params->start_of_list_of_paths;
	i = 1;
	while (paths)
	{
		// printf("%d\n", paths->len_seq);
		// printf("path №%d\n", i);
		seq = paths->seq;
		// printf("start\n");
		seq->room->prev_path = g_params->start;
		while (seq)
		{
			// printf("%s\n", seq->room->name);
			if (seq->next)
			{
				seq->room->next_elem = seq->next->room;
				seq->next->room->prev_path = seq->room;
			}
			else
				seq->room->next_elem = g_params->end;
			seq = seq->next;
		}
		// printf("end\n");
		// printf("-----------------\n");
		paths = paths->next;
		i++;
	}
	// printf("-----------------\n");
	return ;
}

void	print_paths_double(void)
{
	int				i;
	t_neighbour		*seq;
	t_path			*paths;

	paths = g_params->start_of_list_of_paths;
	i = 1;
	while (paths)
	{
		// printf("%d\n", paths->len_seq);
		printf("path №%d\n", i);
		seq = paths->seq;
		printf("start\n");
		seq->room->prev_path = g_params->start;
		while (seq)
		{
			printf("%s\n", seq->room->name);
			if (seq->next)
			{
				seq->room->next_elem = seq->next->room;
				seq->next->room->prev_path = seq->room;
			}
			else
				seq->room->next_elem = g_params->end;
			seq = seq->next;
		}
		printf("end\n");
		printf("-----------------\n");
		paths = paths->next;
		i++;
	}
	printf("-----------------\n");
	return ;
}

int		main(int argc, char **argv)
{
	t_path		*paths;
	int			flows;
	int			nr_steps;

	argc = 0;
	argv = NULL;
	read_input();
	//check_coordinates();
	flows = ft_min(g_params->nr_ants,
			num_of_nghbrs(g_params->start->neighbours),
			num_of_nghbrs(g_params->end->neighbours));
	nr_steps = algorithm(flows, &paths);
	// printf("%d\n", nr_steps);
	print_paths_();
	print_paths_double();
	// print_paths(nr_steps);
	free_g_params();
	return (0);
}
