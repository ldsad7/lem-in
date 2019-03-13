/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 17:40:41 by bsprigga          #+#    #+#             */
/*   Updated: 2019/03/13 19:17:52 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	check_coordinates(void)
{
	t_room		*start_of_list;
	t_room		*tmp;

	if (!g_params)
		return ;
	start_of_list = g_params->start_of_list;
	while (start_of_list)
	{
		tmp = start_of_list->next;
		while (tmp)
		{
			if (tmp->coord_x == start_of_list->coord_x &&
				tmp->coord_y == start_of_list->coord_y)
				error_exit();
			tmp = tmp->next;
		}
		start_of_list = start_of_list->next;
	}
}

int		num_of_nghbrs(t_neighbour *neighbour)
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

int		sum_of_paths(t_path **paths, int flows)
{
	int		sum;
	int		i;

	i = 0;
	sum = 0;
	while (i < flows)
	{
		sum += paths[i]->len_seq;
		i++;
	}
	return (sum);
}

int		ft_min(int a, int b, int c)
{
	if (a <= b && a <= c)
		return (a);
	if (b <= a && b <= c)
		return (b);
	return (c);
}

t_room	**lst_to_array(t_neighbour *nghbr, int len)
{
	int		i;
	t_room	**res;

	res = (t_room **)malloc(sizeof(*res) * len);
	i = 0;
	while (nghbr)
	{
		res[i] = nghbr->room;
		nghbr = nghbr->next;
		i++;
	}
	return (res);
}

void	print_paths(void)
{
	int				i;
	t_neighbour		*seq;
	t_path			*paths;

	paths = g_params->start_of_list_of_paths;
	i = 1;
	while (paths)
	{
		printf("path №%d\n", i);
		printf("start\n");
		seq = paths->seq;
		while (seq)
		{
			printf("%s\n", seq->room->name);
			seq = seq->next;
		}
		printf("end\n");
		printf("-----------------\n");
		paths = paths->next;
		i++;
	}
	return ;
}

int		main(int argc, char **argv)
{
	t_path		*paths;
	int			flows;

	argc = 0;
	argv = NULL;
	read_input();
	check_coordinates();
	flows = ft_min(g_params->nr_ants,
			num_of_nghbrs(g_params->start->neighbours),
			num_of_nghbrs(g_params->end->neighbours));
	algorithm(flows, &paths);
	//print_paths();
	printf("%d\n", flows);
	free_g_params();
	return (0);
}
