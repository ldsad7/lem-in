/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_part_5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 12:25:31 by tsimonis          #+#    #+#             */
/*   Updated: 2019/03/28 05:11:16 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void add_path_main_loop(t_room **room, t_path **path)
{
	t_room		*tmp;
	t_neighbour	*new;

	tmp = *room;
	while (tmp && tmp != g_params->start)
	{
		(*path)->len_seq++;
		if (!(new = (t_neighbour *)malloc(sizeof(t_neighbour))))
			exit(0);
		new->room = tmp;
		new->next = NULL;
		if ((*path)->seq)
			new->next = (*path)->seq;
		(*path)->seq = new;
		tmp->prev_path->next_elem = tmp;
		tmp = tmp->prev_path;
	}
}

void		add_path(t_path **paths, t_room **room)
{
	t_path		*path;

	if (!(path = (t_path *)malloc(sizeof(t_path))))
		exit(0);
	path->len_seq = 1;
	path->seq = NULL;
	path->next = NULL;
	add_path_main_loop(room, &path);
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
