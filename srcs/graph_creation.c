/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 11:53:28 by bsprigga          #+#    #+#             */
/*   Updated: 2019/03/11 12:24:35 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include "lem_in.h"

t_room			*new_room(char *name, int x, int y)
{
	t_room	*tmp;

	if (!(tmp = (t_room	*)malloc(sizeof(t_room))))
		exit(0);
	tmp->coord_x = x;
	tmp->coord_y = y;
	if (!(tmp->name = ft_strdup(name)))
		exit(0);
	tmp->next = NULL;
	tmp->neighbours = NULL;
	return (tmp);
}


// t_level_room	*new_level_room(t_room *room, int level)
// {
// 	t_level_room	*level_room;

// 	if (!(level_room = (t_level_room *)malloc(sizeof(t_level_room))))
// 		exit(0);
// 	level_room->level = level;
// 	level_room->next = NULL;
// 	level_room->room = room;
// 	return (level_room);
// }

// int				bfs_count_level_for_node(int level, t_room *room)
// {
// 	t_neighbour *neighbours;

// 	if (ft_strequ(room->name, g_params->end->name))
// 		return (level);
// 	neighbours = room->neighbours;
// 	while (neighbours)
// 	{
// 		bfs_count_level_for_node(level + 1, neighbours->room);
// 		neighbours->next;
// 	}
// }

t_queue			*queue_elem(t_room *room)
{
	t_queue	*queue_elem;

	if (!(queue_elem = (t_queue *)malloc(sizeof(t_queue))))
		exit(0);
	queue_elem->next = NULL;
	queue_elem->room = room;
	return (queue_elem);
}

void			insert_queue_elem(t_queue *queue, t_queue *queue_elem)
{
	while (queue->next)
		queue = queue->next;
	queue->next = queue_elem;
}

void			build_level_graph(t_room *room)
{
	t_queue			*queue;
	t_queue			*tmp_queue;
	int				level;
	t_neighbour		*neighbours;

	level = 1;
	queue = queue_elem(room);
	while (queue)
	{
		tmp_queue = queue;
		neighbours = queue->room->neighbours;
		while (neighbours)
		{
			if (neighbours->room->visited_for_level == 0)
			{
				neighbours->room->level = level;
				neighbours->room->visited_for_level = 1;
				insert_queue_elem(queue, queue_elem(neighbours->room));
			}
			neighbours = neighbours->next;
		}
		queue = queue->next;
		free(tmp_queue);
		level++;
	}
}
*/
