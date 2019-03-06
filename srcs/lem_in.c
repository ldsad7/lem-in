/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 17:40:41 by bsprigga          #+#    #+#             */
/*   Updated: 2019/03/06 16:11:25 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	check_coordinates(t_params *g_params)
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
				error_exit();
			tmp = tmp->next;
		}
		start_of_list = start_of_list->next;
	}
}

int		main(int argc, char **argv)
{
	t_params	*g_params;
	t_room		**graph;

	argc = 0;
	argv = NULL;
	if (!(g_params = (t_params *)malloc(sizeof(t_params))))
		error_exit();
	g_params_init(g_params, &fls);
	// read_input(g_params);
	// check_coordinates(g_params);
	graph = (t_room **)malloc(sizeof(t_room) * 8);
	graph[0] = new_room("start", 4, 0);
	graph[1] = new_room("1", 4, 2);
	graph[2] = new_room("2", 4, 4);
	graph[3] = new_room("3", 2, 2);
	graph[4] = new_room("4", 0, 4);
	graph[5] = new_room("5", 8, 2);
	graph[6] = new_room("6", 8, 4);
	graph[7] = new_room("end", 4, 6);
	
	graph[0]->next = graph[1];
	graph[0]->next->next = graph[3];
	graph[1]->next = graph[0];
	graph[1]->next->next = graph[2];
	graph[1]->next->next->next = graph[5];
	graph[2]->next = graph[1];
	graph[2]->next->next = graph[4];
	graph[2]->next->next->next = graph[7];
	graph[3]->next = graph[0];
	graph[3]->next->next = graph[4];
	graph[4]->next = graph[3];
	graph[4]->next->next = graph[2];
	graph[5]->next = graph[1];
	graph[5]->next->next = graph[6];
	graph[6]->next = graph[5];
	graph[6]->next->next = graph[7];
	graph[7]->next = graph[6];
	graph[7]->next->next = graph[2];

	build_level_graph(graph);
	
	free_g_params(g_params);
	return (0);
}
