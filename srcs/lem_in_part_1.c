/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_part_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 17:40:41 by bsprigga          #+#    #+#             */
/*   Updated: 2019/03/27 20:47:17 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

// int		sum_of_paths(t_path **paths, int flows)
// {
// 	int		sum;
// 	int		i;

// 	i = 0;
// 	sum = 0;
// 	while (i < flows)
// 	{
// 		sum += paths[i]->len_seq;
// 		i++;
// 	}
// 	return (sum);
// }

// t_room	**lst_to_array(t_neighbour *nghbr, int len)
// {
// 	int		i;
// 	t_room	**res;

// 	res = (t_room **)malloc(sizeof(*res) * len);
// 	i = 0;
// 	while (nghbr)
// 	{
// 		res[i] = nghbr->room;
// 		nghbr = nghbr->next;
// 		i++;
// 	}
// 	return (res);
// }

static void	correct_paths_seq_loop(t_neighbour *seq)
{
	while (seq)
	{
		if (seq->next)
		{
			seq->room->next_elem = seq->next->room;
			seq->next->room->prev_path = seq->room;
		}
		else
			seq->room->next_elem = g_params->end;
		seq = seq->next;
	}
}

void		correct_paths(void)
{
	t_neighbour		*seq;
	t_path			*paths;

	paths = g_params->start_of_list_of_paths;
	while (paths)
	{
		if (!(seq = paths->seq))
		{
			g_params->start->next_elem = g_params->end;
			paths = paths->next;
			continue ;
		}
		else
			seq->room->prev_path = g_params->start;
		// while (seq)
		// {
		// 	if (seq->next)
		// 	{
		// 		seq->room->next_elem = seq->next->room;
		// 		seq->next->room->prev_path = seq->room;
		// 	}
		// 	else
		// 		seq->room->next_elem = g_params->end;
		// 	seq = seq->next;
		// }
		correct_paths_seq_loop(seq);
		paths = paths->next;
	}
}

void		print_paths_double(void)
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
		
		//seq = paths->seq;
		if (!(seq = paths->seq))
		{
			g_params->start->next_elem = g_params->end; //!!!
			paths = paths->next;
			printf("start\n");
			printf("end\n");
			continue ;
		}
		else
			seq->room->prev_path = g_params->start;
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
		// printf("-----------------\n");
		paths = paths->next;
		i++;
	}
	// printf("-----------------\n");
	return ;
}

static int	num_of_nghbrs(t_neighbour *neighbour)
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

static int	ft_min(int a, int b, int c)
{
	if (a <= b && a <= c)
		return (a);
	if (b <= a && b <= c)
		return (b);
	return (c);
}

int			main(int argc, char **argv)
{
	int				flows;
	int				nr_steps;
	int				fd;
	char			*line;
	t_cost_params	*cost_params;

	argc = 0;
	argv = NULL;
	if ((fd = open("tmp.txt", O_WRONLY|O_CREAT, 0777)) < 0)
		exit(0);
	read_input(fd);
	// check_coordinates();
	flows = ft_min(g_params->nr_ants,
			num_of_nghbrs(g_params->start->neighbours),
			num_of_nghbrs(g_params->end->neighbours));
	cost_params = algorithm(flows);
	nr_steps = cost_params->min_cost;
	free(cost_params);
	correct_paths();
	// print_paths_double();
	line = NULL;
	close(fd);
	if ((fd = open("tmp.txt", O_RDONLY)) < 0)
		exit(0);
	while (get_next_line(fd, &line) > 0 && ft_printf("%s\n", line))
		free(line);
	ft_printf("\n");
	close(fd);
	print_paths(nr_steps);
	free_g_params();
	return (0);
}
