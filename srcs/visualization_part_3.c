/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualization_part_3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:54:47 by bsprigga          #+#    #+#             */
/*   Updated: 2019/04/09 13:43:28 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		norminate_nodes_coords(int x_min_max[2], int y_min_max[2])
{
	t_room	*tmp;

	tmp = g_params->start_of_list;
	while (tmp)
	{
		if (x_min_max[0] == x_min_max[1])
			tmp->coord_x = SCREEN_WIDTH / 2;
		else
			tmp->coord_x = (int)(100 + (float)(tmp->coord_x -
			x_min_max[0]) / (float)(x_min_max[1] -
			x_min_max[0]) * (SCREEN_WIDTH - 200));
		if (y_min_max[0] == y_min_max[1])
			tmp->coord_y = SCREEN_HEIGHT / 2;
		else
			tmp->coord_y = (int)(100 + (float)(tmp->coord_y -
			y_min_max[0]) / (float)(y_min_max[1] -
			y_min_max[0]) * (SCREEN_HEIGHT - 200));
		tmp = tmp->next;
	}
}

static void	draw_ants_movement(t_room **room_arr, int cnt_paths,
								int *nr_ants_to_move_in_paths)
{
	t_room		*tmp_room;
	int			i;

	SDL_SetRenderDrawColor(g_params->renderer, 220, 250, 190, 110);
	SDL_RenderClear(g_params->renderer);
	draw_graph();
	i = 0;
	while (i < cnt_paths)
	{
		tmp_room = room_arr[i];
		if (tmp_room == g_params->start)
			tmp_room->ant_nr = g_params->nr_ants;
		print_existing_ants_movement_viz(&tmp_room);
		new_ants_move_in_path_viz(i, tmp_room, &nr_ants_to_move_in_paths);
		if (room_arr[i]->next_elem != g_params->end)
			room_arr[i] = room_arr[i]->next_elem;
		i++;
	}
	if (g_params->nr_ants > 0)
		print_ant(g_params->start);
	SDL_RenderPresent(g_params->renderer);
}

static void	iter_ants_move_viz(int nr_steps, t_room **room_arr,
						int *nr_ants_to_move_in_paths, int cnt_paths)
{
	int			quit;
	SDL_Event	e;

	draw_graph();
	print_ant(g_params->start);
	SDL_RenderPresent(g_params->renderer);
	quit = 0;
	while (!quit)
		while (SDL_PollEvent(&e))
			if ((e.type == KEY_EVENT && e.key.keysym.sym == ESC_KEY)
			|| (e.type == EXIT_CLICK))
			{
				quit = 1;
				break ;
			}
			else if (e.type == KEY_EVENT &&
			e.key.keysym.sym == SPACE_KEY && nr_steps-- > 0)
				draw_ants_movement(room_arr, cnt_paths,
				nr_ants_to_move_in_paths);
}

static void	rooms_arr_setup(t_room ***room_arr, int **nr_ants_to_move_in_paths,
						int cnt_paths, int sum_paths)
{
	t_path		*tmp;
	int			i;

	if (!(*room_arr = (t_room **)malloc(sizeof(t_room *) * cnt_paths)))
		perror_exit("malloc");
	if (!(*nr_ants_to_move_in_paths = (int *)malloc(sizeof(int) * cnt_paths)))
		perror_exit("malloc");
	i = 0;
	tmp = g_params->start_of_list_of_paths;
	while (tmp)
	{
		(*nr_ants_to_move_in_paths)[i] = (g_params->nr_ants + sum_paths)
		/ cnt_paths - tmp->len_seq +
							((g_params->nr_ants + sum_paths) % cnt_paths != 0);
		if (!(tmp->seq))
			(*room_arr)[i] = g_params->start;
		else
			(*room_arr)[i] = tmp->seq->room;
		tmp = tmp->next;
		++i;
	}
}

void		print_paths_for_viz(int nr_steps)
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
	iter_ants_move_viz(nr_steps + 1, room_arr, nr_ants_to_move_in_paths,
						cnt_paths);
	free(nr_ants_to_move_in_paths);
	free(room_arr);
}
