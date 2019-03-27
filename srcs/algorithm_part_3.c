/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_part_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 12:25:31 by tsimonis          #+#    #+#             */
/*   Updated: 2019/03/27 19:12:49 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	bfs_loop_room_in_paths(t_queue *queue, t_stack *fls, int path_nr)
{
	push_queue(&queue, &(queue->room->prev_path));
	push_stack(&fls, 0);
	queue->room->prev_path->path_nr = path_nr;
}

static void	bfs_loop_else(t_neighbour *neighb, t_queue *queue,
							t_stack *fls, int path_nr)
{
	while (neighb && (neighb->room != g_params->end ||
	(neighb->room == g_params->end && queue->room->in_paths)))
	{
		if ((neighb->room->path_nr != path_nr
			|| (neighb->room->path_nr == path_nr && queue->room->in_paths &&
			neighb->room == queue->room->prev_path))
			&& neighb->room != g_params->end && neighb->room != g_params->start
			&& !(queue->room == g_params->start && neighb->room->in_paths)
			&& !(queue->room->in_paths && neighb->room == queue->room->next_elem))
		{
			push_queue(&queue, &(neighb->room));
			neighb->room->path_nr = path_nr;
			if (queue->room->in_paths == neighb->room->in_paths)
				push_stack(&fls, 0);
			else
				push_stack(&fls, 1);
			if (!(queue->room->in_paths) ||
				(queue->room->in_paths && queue->room->in_paths !=
				neighb->room->in_paths))
				neighb->room->prev_elem = queue->room;
		}
		neighb = neighb->next;
	}
}

// fls -- was there an edge of the previous path?

int			bfs(int path_nr, t_room ***paths_ends, t_path **paths)
{
	t_queue			*queue;
	t_stack			*fls;
	t_neighbour		*neighb;

	queue = NULL;
	fls = NULL;
	push_queue(&queue, &(g_params->start));
	push_stack(&fls, 0);
	while (queue)
	{
		if (queue->room->in_paths && fls->value)
			bfs_loop_room_in_paths(queue, fls, path_nr);
		else
		{
			neighb = queue->room->neighbours;
			bfs_loop_else(neighb, queue, fls, path_nr);
			if (neighb && neighb->room == g_params->end)
			{
				(*paths_ends)[path_nr - 1] = queue->room;
				flag_path(*paths_ends, path_nr, paths);
				queue_free(&queue);
				ft_stackdel(&fls);
				return (1);
			}
		}
		queue_delone(&queue);
		ft_stackdelone(&fls);
	}
	return (0);
}
