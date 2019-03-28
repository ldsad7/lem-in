/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_part_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 12:25:31 by tsimonis          #+#    #+#             */
/*   Updated: 2019/03/28 20:20:40 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			free_and_relocate_start_of_list_of_paths(
													t_path *paths_curr_iter)
{
	t_path		*tmp_path;
	t_neighbour	*tmp_neghb;

	while (g_params->start_of_list_of_paths != paths_curr_iter)
	{
		tmp_path = g_params->start_of_list_of_paths->next;
		while (g_params->start_of_list_of_paths->seq)
		{
			tmp_neghb = g_params->start_of_list_of_paths->seq->next;
			free(g_params->start_of_list_of_paths->seq);
			g_params->start_of_list_of_paths->seq = tmp_neghb;
		}
		free(g_params->start_of_list_of_paths);
		g_params->start_of_list_of_paths = tmp_path;
	}
}

static void		free_and_relocate_end_of_list_of_paths(t_path *paths_curr_iter)
{
	t_path		*tmp_path;
	t_neighbour	*tmp_neghb;

	while (paths_curr_iter)
	{
		tmp_path = paths_curr_iter->next;
		while (paths_curr_iter->seq)
		{
			tmp_neghb = paths_curr_iter->seq->next;
			free(paths_curr_iter->seq);
			paths_curr_iter->seq = tmp_neghb;
		}
		free(paths_curr_iter);
		paths_curr_iter = tmp_path;
	}
}

static t_path	*get_curr_iter_paths(t_path **paths_prev_iter,
									t_cost_params *cost_params)
{
	int		iter;
	t_path	*paths;

	iter = 0;
	paths = g_params->start_of_list_of_paths;
	while (++iter < cost_params->num_paths_in_resulting_group)
	{
		*paths_prev_iter = paths;
		paths = paths->next;
	}
	return (paths);
}

static void		get_sum_paths_and_num_paths_in_group(t_path paths,
								int *sum_paths, int *num_paths_in_group)
{
	t_path	*path;

	path = &paths;
	while (path)
	{
		*sum_paths += path->len_seq;
		path = path->next;
		(*num_paths_in_group)++;
	}
}

int				compare(t_cost_params *cost_params, t_path **paths_bfs)
{
	t_path	*paths_curr_iter;
	t_path	*paths_prev_iter;
	int		sum_paths;
	int		curr_cost;
	int		num_paths_in_group;

	sum_paths = 0;
	num_paths_in_group = 0;
	paths_curr_iter = get_curr_iter_paths(&paths_prev_iter, cost_params);
	get_sum_paths_and_num_paths_in_group(*paths_curr_iter, &sum_paths,
											&num_paths_in_group);
	curr_cost = (g_params->nr_ants + sum_paths) / cost_params->path_nr - 1;
	if ((g_params->nr_ants + sum_paths) % cost_params->path_nr != 0)
		curr_cost++;
	if (cost_params->min_cost >= curr_cost)
	{
		cost_params->min_cost = curr_cost;
		free_and_relocate_start_of_list_of_paths(paths_curr_iter);
		return (num_paths_in_group + 1);
	}
	free_and_relocate_end_of_list_of_paths(paths_curr_iter);
	*paths_bfs = paths_prev_iter;
	paths_prev_iter->next = NULL;
	return (0);
}
