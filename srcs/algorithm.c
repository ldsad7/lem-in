/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 20:37:07 by tsimonis          #+#    #+#             */
/*   Updated: 2019/03/08 06:20:21 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

t_queue	*queue_delone(t_queue **top)
{
	t_queue		*res;
	t_queue		*prev;
	t_queue		*next;

	if (!(*top))
		return (*top);
	res = *top;
	prev = (*top)->prev;
	next = (*top)->next;
	free(*top);
	if (prev == next && prev)
	{
		prev->prev = NULL;
		prev->next = NULL;
		*top = prev;
		return (res);
	}
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	*top = prev;
	return (res);
}

void	queue_del(t_queue **top)
{
	while (*top)
		queue_delone(top);
	top = NULL;
}

t_queue	*queue_new(t_room *room, t_queue *prev, t_queue *next)
{
	t_queue	*new;

	if (!(new = (t_queue *)malloc(sizeof(*new))))
		return (NULL);
	new->room = room;
	new->prev = prev;
	new->next = next;
	return (new);
}

int		queue_len(t_queue *top)
{
	t_queue		*tmp;
	int			i;

	if (!top)
		return (0);
	i = 1;
	tmp = top->prev;
	while (tmp && tmp != top && ++i)
		tmp = tmp->prev;
	return (i);
}

void	rotate_forward(t_queue **top)
{
	if (*top && (*top)->prev)
		*top = (*top)->prev;
}

void	push_queue(t_queue **queue, t_room *room)
{
	t_queue		*tmp;
	t_queue		*pmt;

	if (!room)
		return ;
	if (*queue && (*queue)->next)
	{
		pmt = *queue;
		tmp = (*queue)->next;
		*queue = queue_new(room, pmt, tmp);
		tmp->prev = *queue;
		pmt->next = *queue;
	}
	else if (*queue)
	{
		tmp = *queue;
		*queue = queue_new(room, tmp, tmp);
		tmp->next = *queue;
		tmp->prev = *queue;
	}
	else
		*queue = queue_new(room, NULL, NULL);
	rotate_forward(queue);
}

void	add_path(t_path **paths, t_room *room)
{
	t_path		*path;
	t_neighbour	*new;

	if (!(path = (t_path *)malloc(sizeof(t_path))))
		exit(0);
	path->len_seq = 1;
	path->seq = NULL;
	path->next = NULL;
	path->num_path = room->num_path;
	while (room && room != g_params->start)
	{
		path->len_seq++;
		if (!(new = (t_neighbour *)malloc(sizeof(t_neighbour))))
			exit(0);
		new->room = room;
		new->next = NULL;
		if (path->seq)
			new->next = path->seq;
		path->seq = new;
		room = room->prev;
	}
	if (!g_params->start_of_list_of_path)
		g_params->start_of_list_of_path = path;
	if (*paths)
	{
		(*paths)->next = path;
		*paths = (*paths)->next;
	}
	else
		*paths = path;
}

int		disjoint_paths(int flows)
{
	int		num_of_paths;
	t_path	*tmp;
	int		fl;

	flows = flows + 1 - 1;
	tmp = g_params->start_of_list_of_path;
	num_of_paths = 0;
	while (tmp)
	{
		num_of_paths++;
		tmp = tmp->next;
	}
	if (num_of_paths >= flows + 5)
	{
		fl = 0;
		return (1);
	}
	return (0);
}

void	remove_num_path(t_room *room)
{
	int				fl;
	t_neighbour		*neighb;
	t_room			*tmp;

	while (room)
	{
		fl = 0;
		tmp = room->prev;
		room->prev = NULL;
		room->num_path = 0;
		neighb = room->neighbours;
		while (neighb)
		{
			if (neighb->room->num_path > 0
					&& neighb->room->num_path != room->num_path)
			{
				fl = 1;
				break ;
			}
			neighb = neighb->next;
		}
		if (fl)
			break ;
		room = tmp;
	}
}

void	algorithm(int flows, t_path **paths)
{
	t_neighbour	*neighb;
	t_queue		*queue;
	int			num_path;
	int			fl;
	int			empty_place;

	queue = NULL;
	neighb = g_params->start->neighbours;
	num_path = 1;
	while (neighb)
	{
		if (!neighb->room->num_path)
		{
			neighb->room->num_path = num_path;
			push_queue(&queue, neighb->room);
			neighb->room->prev = g_params->start;
			num_path++;
		}
		else
			add_path(paths, neighb->room);
		neighb = neighb->next;
	}
	while (queue)
	{
		//printf("<<<<<<<<<<<<<<<<<<<<\n");
		//print_queue(queue);
		neighb = queue->room->neighbours;
		fl = 0;
		empty_place = 0;
		while (neighb)
		{
			if (neighb->room->num_path > 0
					&& neighb->room->num_path != queue->room->num_path)
				fl = 1;
			else if (neighb->room->num_path == -2)
			{
				add_path(paths, queue->room);
				if (disjoint_paths(flows))
					return ;
				else
				{
					remove_num_path(queue->room);
					queue_delone(&queue);
					fl = 2;
					break ;
				}
			}
			else if (neighb->room->num_path == 0)
				empty_place = 1;
			neighb = neighb->next;
		}
		if (fl == 2)
			continue ;
		if (fl && queue->prev->room != queue->room)
			push_queue(&queue, queue->room);
		if (empty_place)
		{
			neighb = queue->room->neighbours;
			while (neighb)
			{
				if (!neighb->room->num_path)
				{
					neighb->room->num_path = queue->room->num_path;
					push_queue(&queue, neighb->room);
					neighb->room->prev = queue->room;
				}
				neighb = neighb->next;
			}
		}
		queue_delone(&queue);
		//printf(">>>>>>>>>>>>>>>>>>>>>>\n");
	}
}
