/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_part_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 17:40:41 by bsprigga          #+#    #+#             */
/*   Updated: 2019/03/28 22:31:41 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	check_coordinates(void)
{
 	t_room		*start_of_list;
 	t_room		*tmp;

 	start_of_list = g_params->start_of_list;
 	while (start_of_list)
 	{
 		tmp = start_of_list->next;
 		while (tmp)
 		{
 			if (tmp->coord_x == start_of_list->coord_x &&
 				tmp->coord_y == start_of_list->coord_y)
 				error_exit(e_two_nodes_have_the_same_coordinates);
 			tmp = tmp->next;
 		}
		start_of_list = start_of_list->next;
	}
}

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
		correct_paths_seq_loop(seq);
		paths = paths->next;
	}
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

void		recursive_print_and_free(t_list **input)
{
	if (!(*input))
		return;
	recursive_print_and_free(&((*input)->next));
	ft_printf("%s\n", (*input)->content);
	free((*input)->content);
	free(*input);
}

int			main(int argc, char **argv)
{
	int				flows;
	int				nr_steps;
	t_cost_params	*cost_params;
	t_list			*input;

	argc = 0;
	argv = NULL;
	input = NULL;
	read_input(&input);
	check_coordinates();
	flows = ft_min(g_params->nr_ants,
			num_of_nghbrs(g_params->start->neighbours),
			num_of_nghbrs(g_params->end->neighbours));
	cost_params = algorithm(flows);
	nr_steps = cost_params->min_cost;
	free(cost_params);
	correct_paths();
	recursive_print_and_free(&input);
	print_paths(nr_steps);
	free_g_params();
	return (0);
}
