/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualization_part_3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:54:47 by bsprigga          #+#    #+#             */
/*   Updated: 2019/04/08 19:14:34 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	draw_node(int x, int y, int fl)
{
	int		r;
	int		g;
	int		b;

	r = 0;
	g = 255;
	b = 0;
	if (fl == 1) // start or end node
	{
		r = 255;
		g = 0;
		b = 0;
	}
	if (aacircleRGBA(g_params->renderer, x, y, 20, r, g, b, 255) == -1 ||
		filledCircleRGBA(g_params->renderer, x, y, 20, r, g, b, 255) == -1)
		exit(ft_printf("can't draw circle\n"));
}

void	draw_line(int x0, int y0, int x1, int y1)
{
	aalineRGBA(g_params->renderer, x0, y0, x1, y1, 0, 0, 255, 255);
}

static void	print_ant(t_room *room)
{
	g_params->r->x = (int)(100 + (float)(room->coord_x - g_params->x_min_max[0]) /
				(float)(g_params->x_min_max[1] - g_params->x_min_max[0]) * (SCREEN_WIDTH - 200)) - 46;
	g_params->r->y = (int)(100 + (float)(room->coord_y - g_params->x_min_max[0]) /
				(float)(g_params->x_min_max[1] - g_params->x_min_max[0]) * (SCREEN_WIDTH - 200));
	ft_printf("%d,%d\n", g_params->r->x, g_params->r->y);
	SDL_RenderCopy(g_params->renderer, g_params->texture, NULL, g_params->r);
}

static void	new_ants_move_in_path(int i, t_room *room,
								int **nr_ants_to_move_in_paths)
{
	int		fl;

	fl = 0;
	if ((*nr_ants_to_move_in_paths)[i] > 0 && g_params->nr_ants > 0)
	{
		room->ant_nr = g_params->nr_ants;
		g_params->nr_ants--;
		if (room != g_params->start)
			print_ant(room);
		(*nr_ants_to_move_in_paths)[i]--;
	}
}

static void	print_existing_ants_movement(t_room **room)
{
	if ((*room)->next_elem == g_params->end && (*room)->ant_nr)
	{
		print_ant(g_params->end);
		(*room)->ant_nr = 0;
	}
	while ((*room)->prev_path != g_params->start &&
	(*room)->prev_path && (*room)->prev_path->ant_nr)
	{
		(*room)->ant_nr = (*room)->prev_path->ant_nr;
		(*room)->prev_path->ant_nr = 0;
		print_ant(*room);
		(*room) = (*room)->prev_path;
	}
}

static void	iter_ants_move(int nr_steps, t_room **room_arr,
						int *nr_ants_to_move_in_paths, int cnt_paths)
{
	t_room		*tmp_room;
	int			i;
	int			quit;
	SDL_Event	e;

	draw_graph();
	SDL_RenderCopy(g_params->renderer, g_params->texture, NULL, g_params->r);
	SDL_RenderPresent(g_params->renderer);
	quit = 0;
	while (!quit)
		while (SDL_PollEvent(&e))
			if ((e.type == KEY_EVENT && e.key.keysym.sym == ESC_KEY) || (e.type == EXIT_CLICK))
			{
				quit = 1;
				break ;
			}
			else if (e.type == KEY_EVENT && e.key.keysym.sym == SPACE_KEY && nr_steps-- > 0)
			{
				SDL_SetRenderDrawColor(g_params->renderer, 220, 250, 190, 110);
				SDL_RenderClear(g_params->renderer);
				draw_graph();
				i = 0;
				while (i < cnt_paths)
				{
					tmp_room = room_arr[i];
					if (tmp_room == g_params->start)
						tmp_room->ant_nr = g_params->nr_ants;
					print_existing_ants_movement(&tmp_room);
					new_ants_move_in_path(i, tmp_room, &nr_ants_to_move_in_paths);
					if (room_arr[i]->next_elem != g_params->end)
						room_arr[i] = room_arr[i]->next_elem;
					i++;
				}
				SDL_RenderPresent(g_params->renderer);
			}
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
	iter_ants_move(nr_steps + 1, room_arr, nr_ants_to_move_in_paths, cnt_paths);
	free(nr_ants_to_move_in_paths);
	free(room_arr);
}