/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualization_part_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:54:47 by bsprigga          #+#    #+#             */
/*   Updated: 2019/04/08 20:33:19 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	norminate_nodes_coords(int x_min_max[2], int y_min_max[2])
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

void	arrays_filling_and_norminate_coords()
{
	int		x_min_max[2];
	int		y_min_max[2];
	t_room	*tmp;

	tmp = g_params->start_of_list;
	x_min_max[0] = tmp->coord_x;
	x_min_max[1] = tmp->coord_x;
	y_min_max[0] = tmp->coord_y;
	y_min_max[1] = tmp->coord_y;
	tmp = tmp->next;
	while (tmp)
	{
		if (tmp->coord_x < x_min_max[0])
			x_min_max[0] = tmp->coord_x;
		else if (tmp->coord_x > x_min_max[1])
			x_min_max[1] = tmp->coord_x;
		if (tmp->coord_y < y_min_max[0])
			y_min_max[0] = tmp->coord_y;
		else if (tmp->coord_y > y_min_max[1])
			y_min_max[1] = tmp->coord_y;
		tmp = tmp->next;
	}
	norminate_nodes_coords(x_min_max, y_min_max);
}

static void	draw_nodes(void)
{
	t_room	*tmp;
	int		fl;

	tmp = g_params->start_of_list;
	fl = 0;
	while (tmp)
	{
		if (tmp == g_params->start || tmp == g_params->end)
			fl = 1;
		else
			fl = 0;
		draw_node(tmp->coord_x, tmp->coord_y, fl);
		tmp = tmp->next;
	}
}

static void	draw_lines(void)
{
	t_room		*tmp;
	t_neighbour	*neighb;

	tmp = g_params->start_of_list;
	while (tmp)
	{
		neighb = tmp->neighbours;
		while (neighb)
		{
			draw_line(tmp->coord_x, tmp->coord_y,
				neighb->room->coord_x, neighb->room->coord_y);
			neighb = neighb->next;
		}
		tmp = tmp->next;
	}
}

void	draw_graph(void)
{
	draw_lines();
	draw_nodes();
}

void	draw_all(int nr_steps)
{
	SDL_Rect	*r;

	if (!(r = (SDL_Rect *)malloc(sizeof(*r))))
		exit(0);
	r->x = 0;
	r->y = 0;
	r->w = 93;
	r->h = 50;
	g_params->r = r;
	arrays_filling_and_norminate_coords();	
	print_paths_for_viz(nr_steps);
	free(g_params->r);
}

// printf("The %s key was pressed!\n", SDL_GetKeyName(e.key.keysym.sym));
// printf("%d, %d\n", e.key.keysym.sym, e.type);