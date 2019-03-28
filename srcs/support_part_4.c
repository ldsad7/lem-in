/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_part_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 22:42:34 by tsimonis          #+#    #+#             */
/*   Updated: 2019/03/28 23:02:42 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			num_of_nghbrs(t_neighbour *neighbour)
{
	int		i;

	i = 0;
	while (neighbour)
	{
		neighbour = neighbour->next;
		i++;
	}
	return (i);
}

int			ft_min(int a, int b, int c)
{
	if (a <= b && a <= c)
		return (a);
	if (b <= a && b <= c)
		return (b);
	return (c);
}

void		recursive_print_and_free(t_list **input)
{
	if (!(*input))
		return ;
	recursive_print_and_free(&((*input)->next));
	ft_printf("%s\n", (*input)->content);
	free((*input)->content);
	free(*input);
}
