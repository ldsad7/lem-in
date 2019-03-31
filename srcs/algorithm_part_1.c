/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_part_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 12:25:31 by tsimonis          #+#    #+#             */
/*   Updated: 2019/03/31 13:39:56 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		algorithm_neighb_loop(t_cost_params *cost_params,
								t_room **paths_ends, t_path **paths)
{
	t_neighbour	*neighb;
	t_neighbour	*prev;

	neighb = g_params->start->neighbours;
	prev = neighb;
	while (neighb)
	{
		if (neighb->room == g_params->end)
		{
			paths_ends[0] = g_params->start;
			flag_path(paths_ends, 1, paths);
			cost_params->path_nr++;
			cost_params->num_paths_in_resulting_group++;
			cost_params->min_cost = g_params->nr_ants +
					g_params->start_of_list_of_paths->len_seq - 1;
			if (prev != neighb)
				prev->next = neighb->next;
			else
				g_params->start->neighbours = neighb->next;
			free(neighb);
			break ;
		}
		prev = neighb;
		neighb = neighb->next;
	}
}

static void		algorithm_bfs_loop(t_cost_params *cost_params,
							t_room **paths_ends, t_path **paths, int flows)
{
	while (cost_params->path_nr <= flows && bfs(cost_params->path_nr,
	&paths_ends, paths))
	{
		if (cost_params->num_paths_in_resulting_group > 1)
		{
			if ((cost_params->num_paths_in_curr_group =
			compare(cost_params, paths)) > 0)
				cost_params->num_paths_in_resulting_group =
								cost_params->num_paths_in_curr_group;
		}
		else
		{
			if (!(g_params->start_of_list_of_paths))
				error_exit(e_invalid_link);
			cost_params->min_cost = g_params->nr_ants +
			g_params->start_of_list_of_paths->len_seq - 1;
		}
		if (cost_params->path_nr == 1)
			cost_params->num_paths_in_resulting_group++;
		cost_params->path_nr++;
	}
}

t_cost_params	*algorithm(int flows)
{
	t_cost_params	*cost_params;
	t_room			**paths_ends;
	t_path			*paths;

	cost_params = cost_params_setup();
	paths = NULL;
	if (!(paths_ends = (t_room **)malloc(sizeof(t_room *) * flows)))
		perror_exit("malloc");
	algorithm_neighb_loop(cost_params, paths_ends, &paths);
	algorithm_bfs_loop(cost_params, paths_ends, &paths, flows);
	if (!paths)
		error_exit(e_no_possible_flow);
	free(paths_ends);
	return (cost_params);
}
