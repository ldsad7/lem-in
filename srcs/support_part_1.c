/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_part_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 11:40:06 by bsprigga          #+#    #+#             */
/*   Updated: 2019/03/29 18:48:31 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			free_2d_array(char **line)
{
	int i;

	i = -1;
	while (line[++i])
		free(line[i]);
	free(line);
}

void			free_g_params(void)
{
	t_room		*start_of_list;
	t_room		*tmp;
	t_neighbour	*neighb;
	t_neighbour	*pmt;

	start_of_list = g_params->start_of_list;
	while (start_of_list)
	{
		free(start_of_list->name);
		neighb = start_of_list->neighbours;
		while (neighb)
		{
			pmt = neighb;
			neighb = neighb->next;
			free(pmt);
		}
		tmp = start_of_list;
		start_of_list = start_of_list->next;
		free(tmp);
	}
	free_and_relocate_start_of_list_of_paths(NULL);
	free(g_params->arr);
	free(g_params);
}

int				get_next_line_or_exit(char **line)
{
	int nr_bytes_read;

	if ((nr_bytes_read = get_next_line(0, line)) < 0)
		error_exit(e_cannot_read_file);
	return (nr_bytes_read);
}

t_cost_params	*cost_params_setup(void)
{
	t_cost_params *tmp;

	if (!(tmp = (t_cost_params *)malloc(sizeof(t_cost_params))))
		exit(0);
	tmp->min_cost = 0;
	tmp->path_nr = 1;
	tmp->num_paths_in_resulting_group = 1;
	tmp->num_paths_in_curr_group = 0;
	return (tmp);
}

int				ft_min(int a, int b, int c)
{
	if (a <= b && a <= c)
		return (a);
	if (b <= a && b <= c)
		return (b);
	return (c);
}
