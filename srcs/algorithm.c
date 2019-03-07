/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 20:37:07 by tsimonis          #+#    #+#             */
/*   Updated: 2019/03/07 21:17:04 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	queue_delone(t_queue **top)
{
	t_queue		*prev;
	t_queue		*next;

	if (!(*top))
		return ;
	prev = (*top)->prev;
	next = (*top)->next;
	free(*top);
	if (prev == next && prev)
	{
		prev->prev = NULL;
		prev->next = NULL;
		*top = prev;
		return ;
	}
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	*top = prev;
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
	if (*top && (*top)->next)
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
		tmp = (*queue)->next;
		pmt = *queue;
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
}

void	algorithm(void)
{
	t_path		*paths;
	t_neighbour	*neighb;
	t_queue		*queue;
	int			num_path;

	queue = NULL;
	neighb = g_params->start->neighbours;
	num_path = 1;
	while (neighb)
	{
		if (!neighb->room->num_path)
		{
			neighb->room->num_path = num_path++;
			push_queue(&queue, neighb->room);
		}
		else
		{

		}
		neighb = neighb->next;
	}
	while (queue)
	{
		neighb = queue->room->neighbours;

	}
	return ;
}
