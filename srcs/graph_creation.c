/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 11:53:28 by bsprigga          #+#    #+#             */
/*   Updated: 2019/03/07 17:33:23 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	*new_room(char *name, int x, int y)
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

int				bfs_count_level_for_node(int level, t_room *room)
{
	t_neighbour *neighbours;

	
	if (ft_strequ(room->name, g_params->end->name))
		return (level);
	neighbours = room->neighbours;
	while (neighbours)
	{
		
	}
}

t_level_room	*bfs_launch(t_room *room) //build_level_graph
{
	// char *queue;
	char **visited_nodes;
	t_level_room *level_start;
	t_level_room *tmp_level;
	t_room *tmp_room;

	// if (ft_strlen(queue) == 0)
	// 	return (level_start);

	// if (!(queue = (char *)ft_strnew(sizeof(char) * g_params->nr_rooms)))
	// 	exit(0);
	// queue[0] = g_params->start->name;
	level_start->room = room;
	while (room)
	{
		tmp_room = room->next;
		tmp_level->room = room;
		tmp_level->level = bfs_count_level_for_node(0, room);
		room = tmp_room;
	}
	return (level_start);
}
