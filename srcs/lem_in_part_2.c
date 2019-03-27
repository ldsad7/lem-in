/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_part_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 17:40:41 by bsprigga          #+#    #+#             */
/*   Updated: 2019/03/27 14:36:55 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	new_ants_move_in_path(int i, t_room *room, int *space_flag,
								int **nr_ants_to_move_in_paths)
{
	int		fl;

	fl = 0;
	if ((*nr_ants_to_move_in_paths)[i] > 0 && g_params->nr_ants > 0)
	{
		room->ant_nr = g_params->nr_ants;
		g_params->nr_ants--;
		if (*space_flag && room != g_params->start)
			fl += write(1, " ", 1);
		else if (!(*space_flag))
			*space_flag = 1;
		if (room != g_params->start)
			fl += ft_printf("L%i-%s", room->ant_nr, room->name);
		(*nr_ants_to_move_in_paths)[i]--;
	}
	return (fl);
}

static int	print_existing_ants_movement(t_room **room, int *space_flag)
{
	int		fl;

	fl = 0;
	if ((*room)->next_elem == g_params->end && (*room)->ant_nr)
	{
		if (*space_flag)
			fl += write(1, " ", 1);
		else
			*space_flag = 1;
		fl += ft_printf("L%i-%s", (*room)->ant_nr, (*room)->next_elem->name);
		(*room)->ant_nr = 0;
	}
	while ((*room)->prev_path != g_params->start &&
	(*room)->prev_path && (*room)->prev_path->ant_nr)
	{
		(*room)->ant_nr = (*room)->prev_path->ant_nr;
		(*room)->prev_path->ant_nr = 0;
		if (*space_flag)
			fl += write(1, " ", 1);
		else
			*space_flag = 1;
		fl += ft_printf("L%i-%s", (*room)->ant_nr, (*room)->name);
		(*room) = (*room)->prev_path;
	}
	return (fl);
}

static void	iter_ants_move(int nr_steps, t_room **room_arr,
						int *nr_ants_to_move_in_paths, int cnt_paths)
{
	t_room		*tmp_room;
	int			i;
	int			fl;
	int			space_flag;

	nr_steps += 1;
	while (nr_steps--)
	{
		space_flag = 0;
		i = 0;
		fl = 0;
		while (i < cnt_paths)
		{
			tmp_room = room_arr[i];
			if (tmp_room == g_params->start)
				tmp_room->ant_nr = g_params->nr_ants;
			fl += print_existing_ants_movement(&tmp_room, &space_flag);
			fl += new_ants_move_in_path(i, tmp_room, &space_flag, &nr_ants_to_move_in_paths);
			if (room_arr[i]->next_elem != g_params->end)
				room_arr[i] = room_arr[i]->next_elem;
			i++;
		}
		if (fl)
			write(1, "\n", 1);
	}
}

static void	rooms_arr_setup(t_room ***room_arr, int **nr_ants_to_move_in_paths,
						int cnt_paths, int sum_paths)
{
	t_path		*tmp;
	int			i;

	if (!(*room_arr = (t_room **)malloc(sizeof(t_room *) * cnt_paths)))
		exit(0);
	if (!(*nr_ants_to_move_in_paths = (int *)malloc(sizeof(int) * cnt_paths)))
		exit(0);
	i = 0;
	tmp = g_params->start_of_list_of_paths;
	while (tmp)
	{
		(*nr_ants_to_move_in_paths)[i] = (g_params->nr_ants + sum_paths)
		/ cnt_paths - tmp->len_seq + ((g_params->nr_ants + sum_paths) % cnt_paths != 0);
		if (!(tmp->seq))
			(*room_arr)[i] = g_params->start;
		else
			(*room_arr)[i] = tmp->seq->room;
		tmp = tmp->next;
		++i;
	}
}

void		print_paths(int nr_steps)
{
	t_path		*tmp;
	int			sum_paths;
	int			cnt_paths;
	t_room		**room_arr;
	int			*nr_ants_to_move_in_paths;

	sum_paths = 0;
	cnt_paths = 0;
	tmp = g_params->start_of_list_of_paths;
	while (tmp)
	{
		sum_paths += tmp->len_seq;
		cnt_paths++;
		tmp = tmp->next;
	}
	rooms_arr_setup(&room_arr, &nr_ants_to_move_in_paths, cnt_paths, sum_paths);
	iter_ants_move(nr_steps, room_arr, nr_ants_to_move_in_paths, cnt_paths);
	free(nr_ants_to_move_in_paths);
	free(room_arr);
}
