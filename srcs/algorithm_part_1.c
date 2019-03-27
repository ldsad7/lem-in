/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_part_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 12:25:31 by tsimonis          #+#    #+#             */
/*   Updated: 2019/03/27 18:47:26 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
void	print_state_of_map(void)
{
	t_room	*start;

	start = g_params->start_of_list;
	printf("----------------------------------\n");
	while (start)
	{
		printf("------\n");
		printf("room: %s\n", start->name);
		if (start->next_elem)
			printf("next_elem: %s\n", start->next_elem->name);
		else
			printf("next_elem: null\n");
		if (start->prev_path)
			printf("prev_path: %s\n", start->prev_path->name);
		else
			printf("prev_path: null\n");
		if (start->prev_elem)
			printf("prev_elem: %s\n", start->prev_elem->name);
		else
			printf("prev_elem: null\n");
		printf("path_nr: %d\n", start->path_nr);
		printf("in_paths: %d\n", start->in_paths);
		printf("------\n");
		start = start->next;
	}
	printf("----------------------------------\n");
}
*/

// void	print_queue(t_queue *queue)
// {
// 	t_queue		*start;

// 	if (!queue)
// 	{
// 		printf("\n");
// 		return ;
// 	}
// 	start = queue;
// 	printf("%s, ", start->room->name);
// 	if (!queue->prev)
// 	{
// 		printf("\n");
// 		return ;
// 	}
// 	queue = queue->prev;
// 	while (queue != start)
// 	{
// 		printf("%s, ", queue->room->name);
// 		queue = queue->prev;
// 	}
// 	printf("\n");
// }



// int		ft_lstlen(t_stack *top)
// {
// 	t_stack	*tmp;
// 	int		i;

// 	if (!top)
// 		return (0);
// 	i = 1;
// 	tmp = top->prev;
// 	while (tmp && tmp != top && ++i)
// 		tmp = tmp->prev;
// 	return (i);
// }

// int		queue_len(t_queue *queue)
// {
// 	t_queue		*tmp;
// 	int			i;

// 	if (!queue)
// 		return (0);
// 	tmp = queue->prev;
// 	i = 1;
// 	while (tmp && tmp != queue && ++i)
// 		tmp = tmp->prev;
// 	return (i);
// }

static void	algorithm_neighb_loop(t_cost_params *cost_params,
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

static void	algorithm_bfs_loop(t_cost_params *cost_params, t_room **paths_ends,
								t_path **paths, int flows)
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
				error_exit();
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
	t_neighbour		*neighb;
	t_neighbour		*prev;
	t_path			*paths;

	cost_params = cost_params_setup();
	paths = NULL;
	if (!(paths_ends = (t_room **)malloc(sizeof(t_room *) * flows)))
		exit(0);
	neighb = g_params->start->neighbours;
	prev = neighb;
	algorithm_neighb_loop(cost_params, paths_ends, &paths);
	algorithm_bfs_loop(cost_params, paths_ends, &paths, flows);
	free(paths_ends);
	return (cost_params);
}
