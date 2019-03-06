/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 11:53:28 by bsprigga          #+#    #+#             */
/*   Updated: 2019/03/06 17:47:18 by bsprigga         ###   ########.fr       */
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

t_room	**build_level_graph(t_room **graph, char *queue, t_room	*level_graph)
{
	if (ft_strlen(queue) == 0)
		return 

	if (!(queue = (char *)ft_strnew(sizeof(char) * g_params->nr_rooms)))
		exit(0);
	queue[0] = g_params->start->name;
	
}
