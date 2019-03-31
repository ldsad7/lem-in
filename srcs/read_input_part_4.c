/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input_part_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 10:41:48 by bsprigga          #+#    #+#             */
/*   Updated: 2019/03/31 15:03:45 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		check_data_sufficiency(void)
{
	if (!(g_params->nr_ants))
		error_exit(e_no_ants_value);
	else if (!(g_params->start))
		error_exit(e_no_start_node);
	else if (!(g_params->end))
		error_exit(e_no_end_node);
}

void		add_to_lst(t_room *input, t_room *output)
{
	t_neighbour	*neighb;

	if (!(neighb = (t_neighbour *)malloc(sizeof(*neighb))))
		perror_exit("malloc");
	neighb->room = input;
	if (output->neighbours)
		neighb->next = output->neighbours;
	else
		neighb->next = NULL;
	output->neighbours = neighb;
}

static void	sort_list_to_arr_main_loop(int i, t_room *start_of_list)
{
	int		j;
	int		tmp;

	while (start_of_list)
	{
		j = 0;
		while (j < i)
		{
			if (ft_strcmp(g_params->arr[j]->name, start_of_list->name) > 0)
				break ;
			j++;
		}
		tmp = i;
		while (tmp > j)
		{
			g_params->arr[tmp] = g_params->arr[tmp - 1];
			tmp--;
		}
		g_params->arr[tmp] = start_of_list;
		start_of_list = start_of_list->next;
		i++;
	}
}

void		sort_list_to_arr(void)
{
	int		i;

	if (!(g_params->arr = (t_room **)malloc(sizeof(t_room *) *
										(g_params->nr_rooms))))
		perror_exit("malloc");
	i = 0;
	sort_list_to_arr_main_loop(i, g_params->start_of_list);
}
