/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input_part_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 10:41:48 by bsprigga          #+#    #+#             */
/*   Updated: 2019/03/29 12:30:13 by bsprigga         ###   ########.fr       */
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
		exit(0);
	i = 0;
	sort_list_to_arr_main_loop(i, g_params->start_of_list);
}
