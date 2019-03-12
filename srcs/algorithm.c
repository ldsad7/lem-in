/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 12:25:31 by tsimonis          #+#    #+#             */
/*   Updated: 2019/03/12 18:34:11 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	print_queue(t_queue *queue)
{
	t_queue		*start;

	if (!queue)
	{
		printf("\n");
		return ;
	}
	start = queue;
	printf("%s, ", start->room->name);
	if (!queue->prev)
	{
		printf("\n");
		return ;
	}
	queue = queue->prev;
	while (queue != start)
	{
		printf("%s, ", queue->room->name);
		queue = queue->prev;
	}
	printf("\n");
}

void	queue_delone(t_queue **queue)
{
	t_queue		*res;
	t_queue		*prev;
	t_queue		*next;

	if (!(*queue))
		return ;
	res = *queue;
	prev = (*queue)->prev;
	next = (*queue)->next;
	free(*queue);
	if (prev == next && prev)
	{
		prev->prev = NULL;
		prev->next = NULL;
		*queue = prev;
		return ;
	}
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	*queue = prev;
}

void	queue_free(t_queue **queue)
{
	while (*queue)
		queue_delone(queue);
}

t_queue	*queue_new(t_room **room, t_queue **prev, t_queue **next)
{
	t_queue	*new;

	if (!(new = (t_queue *)malloc(sizeof(*new))))
		exit(0);
	new->room = *room;
	if (prev)
		new->prev = *prev;
	else
		new->prev = NULL;
	if (next)
		new->next = *next;
	else
		new->next = NULL;
	return (new);
}

int		queue_len(t_queue *queue)
{
	t_queue		*tmp;
	int			i;

	if (!queue)
		return (0);
	tmp = queue->prev;
	i = 1;
	while (tmp && tmp != queue && ++i)
		tmp = tmp->prev;
	return (i);
}

void	rotate_forward(t_queue **queue)
{
	if (*queue && (*queue)->prev)
		*queue = (*queue)->prev;
}

void	push_queue(t_queue **queue, t_room **room)
{
	t_queue		*tmp;
	t_queue		*pmt;

	if (!(*room))
		return ;
	if (*queue && (*queue)->next)
	{
		pmt = *queue;
		tmp = (*queue)->next;
		*queue = queue_new(room, &pmt, &tmp);
		tmp->prev = *queue;
		pmt->next = *queue;
	}
	else if (*queue)
	{
		tmp = *queue;
		*queue = queue_new(room, &tmp, &tmp);
		tmp->next = *queue;
		tmp->prev = *queue;
	}
	else
		*queue = queue_new(room, NULL, NULL);
	rotate_forward(queue);
}

void	flag_path(t_room **paths_ends, int path_nr) // t_room **room
{
	t_room *room;

	while (--path_nr > -1 && (room = paths_ends[path_nr]))
	{
		room->next_elem = g_params->end;
		while (room && room != g_params->start)
		{
			room->in_paths = 1;
			if (!room->prev_elem->in_paths)
				room->prev_path = room->prev_elem;
			if (room->prev_path)
				room->prev_path->next_elem = room;
			room = room->prev_elem;
		}
	}
}

void	add_path(t_path **paths, t_room **room)
{
	t_path		*path;
	t_neighbour	*new;

	if (!(path = (t_path *)malloc(sizeof(t_path))))
		exit(0);
	path->len_seq = 1;
	path->seq = NULL;
	path->next = NULL;
	(*room)->next_elem = g_params->end;
	while (*room && *room != g_params->start)
	{
		path->len_seq++;
		if (!(new = (t_neighbour *)malloc(sizeof(t_neighbour))))
			exit(0);
		new->room = *room;
		new->next = NULL;
		if (path->seq)
		{
			new->next = path->seq;
			(*room)->next_elem = path->seq->room;
		}
		path->seq = new;
		*room = (*room)->prev_path;
	}
	if (!g_params->start_of_list_of_paths)
		g_params->start_of_list_of_paths = path;
	if (*paths)
	{
		(*paths)->next = path;
		*paths = (*paths)->next;
	}
	else
		*paths = path;
}

/*
**	fl -- was there an edge of the previous path?
*/

int		bfs(int path_nr, t_room ***paths_ends)
{
	t_queue			*queue;
	t_neighbour		*neighb;
	int				fl;

	fl = 1;
	queue = NULL;
	g_params->start->path_nr = path_nr;
	push_queue(&queue, &(g_params->start));
	while (queue)
	{
		print_queue(queue);
		if (fl && queue->room->in_paths)
		{
			if (queue->room->path_nr != path_nr || queue->room->prev_path->path_nr != path_nr)
			{
				push_queue(&queue, &(queue->room->prev_path));
				queue->room->prev_path->path_nr = path_nr;
				fl = 0;
			}
		}
		else
		{
			neighb = queue->room->neighbours;
			while (neighb && (neighb->room != g_params->end ||
			(neighb->room == g_params->end && queue->room->in_paths)))
			{
				if (neighb->room->path_nr != path_nr && neighb->room != g_params->end && !(queue->room == g_params->start && neighb->room->in_paths))
				{
					push_queue(&queue, &(neighb->room));
					neighb->room->path_nr = path_nr;
					if (!(neighb->room->in_paths) || !(queue->room->in_paths))
						neighb->room->prev_elem = queue->room;
				}
				neighb = neighb->next;
			}
			if (neighb && neighb->room == g_params->end)
			{
				(*paths_ends)[path_nr - 1] = queue->room;
				flag_path(*paths_ends, path_nr);
				queue_free(&queue);
				return (1);
			}
		}
		queue_delone(&queue);
	}
	return (0);
}

void	algorithm(int flows, t_path **paths)
{
	int			i;
	t_neighbour *end_neighbours;
	t_room		**paths_ends;

	if (!(paths_ends = (t_room **)malloc(sizeof(t_room *) * flows)))
		exit(0);
	i = 1;
	while (i <= flows && bfs(i, &paths_ends))
		i++;
	end_neighbours = g_params->end->neighbours;
	while (i > 0 && end_neighbours)
	{
		if (end_neighbours->room->in_paths)
		{
			add_path(paths, &(end_neighbours->room));
			i--;
		}
		end_neighbours = end_neighbours->next;
	}
}
