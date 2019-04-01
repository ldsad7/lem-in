/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_part_5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 02:05:57 by tsimonis          #+#    #+#             */
/*   Updated: 2019/04/02 00:03:45 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		free_and_print_warning(char *line)
{
	free(line);
	if (get_next_line(0, &line) > 0)
		ft_printf("WARNING: File wasn't read completely!\n");
	free(line);
}

int			check_link(t_room *tmps[2])
{
	t_neighbour	*input_neighb;

	input_neighb = tmps[0]->neighbours;
	while (input_neighb)
	{
		if (input_neighb->room == tmps[1])
			return (1);
		input_neighb = input_neighb->next;
	}
	add_to_lst(tmps[1], tmps[0]);
	add_to_lst(tmps[0], tmps[1]);
	return (0);
}

void		perror_exit(char *error_message)
{
	perror(error_message);
	exit(2);
}

int			free_and_return_one(char *first_name, char *second_name)
{
	free(first_name);
	free(second_name);
	return (1);
}
