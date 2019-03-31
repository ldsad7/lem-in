/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_part_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 11:40:06 by bsprigga          #+#    #+#             */
/*   Updated: 2019/03/31 13:44:07 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
		perror_exit("malloc");
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
	rotate_forward_queue(queue);
}

void	rotate_forward_queue(t_queue **queue)
{
	if (*queue && (*queue)->prev)
		*queue = (*queue)->prev;
}
