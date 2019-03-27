/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_part_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 11:40:06 by bsprigga          #+#    #+#             */
/*   Updated: 2019/03/27 15:17:50 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

void	ft_stackdel(t_stack **top)
{
	while (*top)
		ft_stackdelone(top);
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

void	rotate_forward_stack(t_stack **top)
{
	if (!(*top) || !((*top)->next))
		return ;
	*top = (*top)->prev;
}
