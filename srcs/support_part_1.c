/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_part_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 11:40:06 by bsprigga          #+#    #+#             */
/*   Updated: 2019/03/28 21:29:30 by tsimonis         ###   ########.fr       */
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

void			error_exit(int value)
{
	free_g_params();
	if (value == e_no_ants_value)
		ft_putstr("ERROR: no ants value\n");
	else if (value == e_ants_value_bigger_int)
		ft_putstr("ERROR: ants' value bigger than int\n");
	else if (value == e_no_start_end_node)
		ft_putstr("ERROR: no start or end node\n");
	else if (value == e_room_starts_with_L)
		ft_putstr("ERROR: room starts with \"L\"\n");
	else if (value == e_invalid_coordinates)
		ft_putstr("ERROR: node has invalid coordinates\n");
	else if (value == e_invalid_link)
		ft_putstr("ERROR: invalid or no links in input file\n");
	else if (value == e_invalid_node)
		ft_putstr("ERROR: invalid or no nodes in input file\n");
	else if (value == e_cannot_read_file)
		ft_putstr("ERROR: cannot read from file\n");
	else if (value == e_two_nodes_have_the_same_coordinates)
		ft_putstr("ERROR: two nodes have the same coordinates\n");
	else
		ft_putstr("ERROR\n");
	exit(0);
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
