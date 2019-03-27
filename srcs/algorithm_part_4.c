/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_part_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 12:25:31 by tsimonis          #+#    #+#             */
/*   Updated: 2019/03/27 19:21:05 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void add_path_main_loop(t_room **room, t_path *path)
{
	t_room		*tmp;
	t_neighbour	*new;

	tmp = *room;
	while (tmp && tmp != g_params->start)
	{
		path->len_seq++;
		if (!(new = (t_neighbour *)malloc(sizeof(t_neighbour))))
			exit(0);
		new->room = tmp;
		new->next = NULL;
		if (path->seq)
			new->next = path->seq;
		path->seq = new;
		tmp->prev_path->next_elem = tmp;
		tmp = tmp->prev_path;
	}
}

void		add_path(t_path **paths, t_room **room)
{
	t_path		*path;
	// t_neighbour	*new;
	// t_room		*tmp;

	if (!(path = (t_path *)malloc(sizeof(t_path))))
		exit(0);
	path->len_seq = 1;
	path->seq = NULL;
	path->next = NULL;
	// tmp = *room;
	// while (tmp && tmp != g_params->start)
	// {
	// 	path->len_seq++;
	// 	if (!(new = (t_neighbour *)malloc(sizeof(t_neighbour))))
	// 		exit(0);
	// 	new->room = tmp;
	// 	new->next = NULL;
	// 	if (path->seq)
	// 		new->next = path->seq;
	// 	path->seq = new;
	// 	tmp->prev_path->next_elem = tmp;
	// 	tmp = tmp->prev_path;
	// }
	add_path_main_loop(room, path);
	if (!(g_params->start_of_list_of_paths))
		g_params->start_of_list_of_paths = path;
	if (*paths)
	{
		(*paths)->next = path;
		*paths = (*paths)->next;
	}
	else
		*paths = path;
}

void		flag_path(t_room **paths_ends, int path_nr, t_path **paths)
{
	t_room	*room;
	int		fl;
	int		tmp;
	int		prev_path;
	int		top_path_nr;

	top_path_nr = path_nr;
	prev_path = 0;
	room = paths_ends[path_nr - 1];
	room->next_elem = g_params->end;
	while (room != g_params->start)
	{
		if (room->in_paths && !prev_path)
			prev_path = room->in_paths;
		room->in_paths = path_nr;
		if (!(room->prev_path))
			room->prev_path = room->prev_elem;
		room->prev_path->next_elem = room;
		room = room->prev_path;
	}
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
			{
				while (room->prev_elem == room->prev_path)
				{
					room->in_paths = 0;
					room = room->next_elem;
				}
				fl = 1;
				room->prev_path = room->prev_elem;
			}
			room = room->prev_path;
		}
		path_nr = prev_path;
		prev_path = tmp;
	}
	tmp = 0;
	while (tmp++ < top_path_nr)
		add_path(paths, &(paths_ends[tmp - 1]));
	room = g_params->start_of_list;
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
