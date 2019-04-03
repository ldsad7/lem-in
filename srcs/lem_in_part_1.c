/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_part_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 17:40:41 by bsprigga          #+#    #+#             */
/*   Updated: 2019/04/03 16:05:14 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

int			main(int argc, char **argv)
{
	int				flows;
	int				nr_steps;
	t_cost_params	*cost_params;
	t_list			*input;

	input = NULL;
	read_input(&input);
	flows = ft_min(g_params->nr_ants,
			num_of_nghbrs(g_params->start->neighbours),
			num_of_nghbrs(g_params->end->neighbours));
	cost_params = algorithm(flows);
	nr_steps = cost_params->min_cost;
	free(cost_params);
	correct_paths();
	recursive_print_and_free(&input);
	ft_printf("\n");
	print_paths(nr_steps);
	free_g_params();
	visualize(argc, argv);
	return (0);
}
