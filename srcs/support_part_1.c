/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_part_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 11:40:06 by bsprigga          #+#    #+#             */
/*   Updated: 2019/03/07 20:15:15 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	free_2d_array(char **line)
{
	int i;

	i = -1;
	while (line[++i])
		free(line[i]);
	free(line);
}

void	free_g_params(void)
{
	t_room		*start_of_list;
	t_room		*tmp;
	t_neighbour	*neighb;
	t_neighbour	*pmt;

	if (!g_params)
		return ;
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
	free(g_params->arr);
	free(g_params);
}

void	error_exit(void)
{
	free_g_params();
	ft_putstr("ERROR");
	exit(0);
}

int		get_next_line_or_exit(char **line)
{
	int nr_bytes_read;

	if ((nr_bytes_read = get_next_line(0, line)) < 0)
		error_exit();
	return (nr_bytes_read);
}
