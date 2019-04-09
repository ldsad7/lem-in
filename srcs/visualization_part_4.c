/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualization_part_4.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:54:47 by bsprigga          #+#    #+#             */
/*   Updated: 2019/04/09 13:40:16 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**	fl - start or end node
*/

void	draw_node(int x, int y, int fl)
{
	int		r;
	int		g;
	int		b;

	r = 0;
	g = 255;
	b = 0;
	if (fl == 1)
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

void	print_ant(t_room *room)
{
	g_params->r->x = room->coord_x - 46;
	g_params->r->y = room->coord_y - 25;
	SDL_RenderCopy(g_params->renderer, g_params->texture, NULL, g_params->r);
}

void	new_ants_move_in_path_viz(int i, t_room *room,
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

void	print_existing_ants_movement_viz(t_room **room)
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
