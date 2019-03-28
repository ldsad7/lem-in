/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_part_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 12:25:31 by tsimonis          #+#    #+#             */
/*   Updated: 2019/03/28 20:38:15 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**	this is where we iterate on newly found paths and checking whether
**	current in_paths number is equal to path_nr. If so, we rollback to
**	node where prev_path != prev_elem and assign prev_elem to prev_path
*/

static void	flag_path_main_loop_rollback(t_room **room, int *fl)
{
	while ((*room)->prev_elem == (*room)->prev_path)
	{
		(*room)->in_paths = 0;
		(*room) = (*room)->next_elem;
	}
	*fl = 1;
	(*room)->prev_path = (*room)->prev_elem;
}

static void	flag_path_main_loop(t_room **paths_ends, int prev_path,
								int path_nr)
{
	int		fl;
	int		tmp;
	t_room	*room;

	while (prev_path)
	{
		tmp = 0;
		fl = 0;
		room = paths_ends[prev_path - 1];
		while (room != g_params->start)
		{
			if (room->in_paths != prev_path && !tmp)
				tmp = room->in_paths;
			room->in_paths = prev_path;
			if (fl && !(room->prev_path))
				room->prev_path = room->prev_elem;
			if (!fl && room->prev_path->in_paths == path_nr)
				flag_path_main_loop_rollback(&room, &fl);
			room = room->prev_path;
		}
		path_nr = prev_path;
		prev_path = tmp;
	}
}

static void	flag_path_create_first_path(t_room **room, int path_nr,
										int *prev_path)
{
	*prev_path = 0;
	while (*room != g_params->start)
	{
		if ((*room)->in_paths && !(*prev_path))
			*prev_path = (*room)->in_paths;
		(*room)->in_paths = path_nr;
		if (!((*room)->prev_path))
			(*room)->prev_path = (*room)->prev_elem;
		(*room)->prev_path->next_elem = *room;
		(*room) = (*room)->prev_path;
	}
}

static void	flag_paths_nulling_nodes_not_in_paths(t_room *room)
{
	while (room)
	{
		if (!(room->in_paths))
		{
			room->prev_elem = NULL;
			room->prev_path = NULL;
			room->next_elem = NULL;
			room->path_nr = 0;
		}
		room = room->next;
	}
}

void		flag_path(t_room **paths_ends, int path_nr, t_path **paths)
{
	t_room	*room;
	int		tmp;
	int		prev_path;
	int		top_path_nr;

	top_path_nr = path_nr;
	prev_path = 0;
	room = paths_ends[path_nr - 1];
	room->next_elem = g_params->end;
	flag_path_create_first_path(&room, path_nr, &prev_path);
	flag_path_main_loop(paths_ends, prev_path, path_nr);
	tmp = 0;
	while (tmp++ < top_path_nr)
		add_path(paths, &(paths_ends[tmp - 1]));
	room = g_params->start_of_list;
	flag_paths_nulling_nodes_not_in_paths(room);
}
