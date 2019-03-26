/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 12:25:31 by tsimonis          #+#    #+#             */
/*   Updated: 2019/03/20 19:34:43 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
void	print_state_of_map(void)
{
	t_room	*start;

	start = g_params->start_of_list;
	printf("----------------------------------\n");
	while (start)
	{
		printf("------\n");
		printf("room: %s\n", start->name);
		if (start->next_elem)
			printf("next_elem: %s\n", start->next_elem->name);
		else
			printf("next_elem: null\n");
		if (start->prev_path)
			printf("prev_path: %s\n", start->prev_path->name);
		else
			printf("prev_path: null\n");
		if (start->prev_elem)
			printf("prev_elem: %s\n", start->prev_elem->name);
		else
			printf("prev_elem: null\n");
		printf("path_nr: %d\n", start->path_nr);
		printf("in_paths: %d\n", start->in_paths);
		printf("------\n");
		start = start->next;
	}
	printf("----------------------------------\n");
}
*/

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

void	ft_stackdelone(t_stack **top)
{
	t_stack	*prev;
	t_stack	*next;

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

void	ft_stackdel(t_stack **top)
{
	while (*top)
		ft_stackdelone(top);
}

void	queue_free(t_queue **queue)
{
	while (*queue)
		queue_delone(queue);
}

t_stack	*ft_stacknew(int value, t_stack *prev, t_stack *next)
{
	t_stack	*new;

	if (!(new = (t_stack *)malloc(sizeof(*new))))
		return (NULL);
	new->value = value;
	new->prev = prev;
	new->next = next;
	return (new);
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

int		ft_lstlen(t_stack *top)
{
	t_stack	*tmp;
	int		i;

	if (!top)
		return (0);
	i = 1;
	tmp = top->prev;
	while (tmp && tmp != top && ++i)
		tmp = tmp->prev;
	return (i);
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

int		rotate_forward_stack(t_stack **top)
{
	if (!(*top) || !((*top)->next))
		return (1);
	*top = (*top)->prev;
	return (1);
}

void	rotate_forward(t_queue **queue)
{
	if (*queue && (*queue)->prev)
		*queue = (*queue)->prev;
}

void	push_stack(t_stack **stack, int value)
{
	t_stack		*tmp;
	t_stack		*pmt;

	if (*stack && (*stack)->next)
	{
		pmt = *stack;
		tmp = (*stack)->next;
		*stack = ft_stacknew(value, pmt, tmp);
		tmp->prev = *stack;
		pmt->next = *stack;
	}
	else if (*stack)
	{
		tmp = *stack;
		*stack = ft_stacknew(value, tmp, tmp);
		tmp->next = *stack;
		tmp->prev = *stack;
	}
	else
		*stack = ft_stacknew(value, NULL, NULL);
	rotate_forward_stack(stack);
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

void	flag_path(t_room **paths_ends, int path_nr, t_path **paths)
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

void	add_path(t_path **paths, t_room **room)
{
	t_path		*path;
	t_neighbour	*new;
	t_room		*tmp;

	if (!(path = (t_path *)malloc(sizeof(t_path))))
		exit(0);
	path->len_seq = 1;
	path->seq = NULL;
	path->next = NULL;
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

// fls -- was there an edge of the previous path?

int		bfs(int path_nr, t_room ***paths_ends, t_path **paths)
{
	t_queue			*queue;
	t_stack			*fls;
	t_neighbour		*neighb;

	queue = NULL;
	fls = NULL;
	push_queue(&queue, &(g_params->start));
	push_stack(&fls, 0);
	while (queue)
	{
		if (queue->room->in_paths && fls->value)
		{
			push_queue(&queue, &(queue->room->prev_path));
			push_stack(&fls, 0);
			queue->room->prev_path->path_nr = path_nr;
		}
		else
		{
			neighb = queue->room->neighbours;
			while (neighb && (neighb->room != g_params->end ||
							(neighb->room == g_params->end && queue->room->in_paths)))
			{
				if ((neighb->room->path_nr != path_nr
					|| (neighb->room->path_nr == path_nr && queue->room->in_paths && neighb->room == queue->room->prev_path))
					&& neighb->room != g_params->end && neighb->room != g_params->start
					&& !(queue->room == g_params->start && neighb->room->in_paths)
					&& !(queue->room->in_paths && neighb->room == queue->room->next_elem))
				{
					push_queue(&queue, &(neighb->room));
					neighb->room->path_nr = path_nr;
					if (queue->room->in_paths == neighb->room->in_paths) //  || !(neighb->room->in_paths)
						push_stack(&fls, 0);
					else
						push_stack(&fls, 1);
					if (!(queue->room->in_paths) ||
						(queue->room->in_paths && queue->room->in_paths != neighb->room->in_paths))
						neighb->room->prev_elem = queue->room;
				}
				neighb = neighb->next;
			}
			if (neighb && neighb->room == g_params->end)
			{
				(*paths_ends)[path_nr - 1] = queue->room;
				flag_path(*paths_ends, path_nr, paths);
				queue_free(&queue);
				ft_stackdel(&fls);
				return (1);
			}
		}
		queue_delone(&queue);
		ft_stackdelone(&fls);
	}
	return (0);
}

void	free_and_relocate_start_of_list_of_paths(t_path *paths_curr_iter)
{
	t_path		*tmp_path;
	t_neighbour	*tmp_neghb;

	while (g_params->start_of_list_of_paths != paths_curr_iter)
	{
		tmp_path = g_params->start_of_list_of_paths->next;
		while (g_params->start_of_list_of_paths->seq)
		{
			tmp_neghb = g_params->start_of_list_of_paths->seq->next;
			free(g_params->start_of_list_of_paths->seq);
			g_params->start_of_list_of_paths->seq = tmp_neghb;
		}
		free(g_params->start_of_list_of_paths);
		g_params->start_of_list_of_paths = tmp_path;
	}
}

void	free_and_relocate_end_of_list_of_paths(t_path *paths_curr_iter)
{
	t_path		*tmp_path;
	t_neighbour	*tmp_neghb;

	while (paths_curr_iter)
	{
		tmp_path = paths_curr_iter->next;
		while (paths_curr_iter->seq)
		{
			tmp_neghb = paths_curr_iter->seq->next;
			free(paths_curr_iter->seq);
			paths_curr_iter->seq = tmp_neghb;
		}
		free(paths_curr_iter);
		paths_curr_iter = tmp_path;
	}
}

int		compare(int *min_cost, int nr_paths, int j, t_path **paths_bfs)
{
	t_path	*paths;
	t_path	*paths_curr_iter;
	t_path	*paths_prev_iter;
	int		sum_paths;
	int		curr_cost;
	int		iter;
	int		cnt_paths_moved;

	paths = g_params->start_of_list_of_paths;
	sum_paths = 0;
	iter = 0;
	cnt_paths_moved = 0;
	while (++iter < j)
	{
		paths_prev_iter = paths;
		paths = paths->next;
	}
	paths_curr_iter = paths;
	while (paths)
	{
		sum_paths += paths->len_seq;
		paths = paths->next;
		cnt_paths_moved++;
	}
	curr_cost = (g_params->nr_ants + sum_paths) / nr_paths - 1;
	if ((g_params->nr_ants + sum_paths) % nr_paths != 0)
		curr_cost++;
	if (*min_cost >= curr_cost)
	{
		*min_cost = curr_cost;
		free_and_relocate_start_of_list_of_paths(paths_curr_iter);
		return (cnt_paths_moved + 1);
	}
	free_and_relocate_end_of_list_of_paths(paths_curr_iter);
	*paths_bfs = paths_prev_iter;
	paths_prev_iter->next = NULL;
	return (0);
}

int		algorithm(int flows, t_path **paths)
{
	int			i;
	int			j;
	int			tmp;
	int			min_cost;
	t_room		**paths_ends;

	min_cost = 0;
	*paths = NULL;
	if (!(paths_ends = (t_room **)malloc(sizeof(t_room *) * flows)))
		exit(0);
	i = 1;
	j = 1;
	while (i <= flows && bfs(i, &paths_ends, paths))
	{
		if (j > 1)
		{
			if ((tmp = compare(&min_cost, i, j, paths)) > 0)
				j = tmp;
		}
		else
		{
			if (!(g_params->start_of_list_of_paths))
				error_exit();
			min_cost = g_params->nr_ants +
			g_params->start_of_list_of_paths->len_seq - 1;
		}
		if (i == 1)
			j++;
		i++;
	}
	return (min_cost);
}
