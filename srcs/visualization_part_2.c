/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualization_part_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:54:47 by bsprigga          #+#    #+#             */
/*   Updated: 2019/04/08 17:41:14 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	arrays_filling(int (*x_min_max)[2], int (*y_min_max)[2])
{
	t_room	*tmp;

	tmp = g_params->start_of_list;
	(*x_min_max)[0] = tmp->coord_x;
	(*x_min_max)[1] = tmp->coord_x;
	(*y_min_max)[0] = tmp->coord_y;
	(*y_min_max)[1] = tmp->coord_y;
	tmp = tmp->next;
	while (tmp)
	{
		if (tmp->coord_x < (*x_min_max)[0])
			(*x_min_max)[0] = tmp->coord_x;
		else if (tmp->coord_x > (*x_min_max)[1])
			(*x_min_max)[1] = tmp->coord_x;
		if (tmp->coord_y < (*y_min_max)[0])
			(*y_min_max)[0] = tmp->coord_y;
		else if (tmp->coord_y > (*y_min_max)[1])
			(*y_min_max)[1] = tmp->coord_y;
		tmp = tmp->next;
	}	
}

static void	draw_nodes(int x_min_max[2], int y_min_max[2])
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
		draw_node((int)(100 + (float)(tmp->coord_x - x_min_max[0]) /
			(float)(x_min_max[1] - x_min_max[0]) * (SCREEN_WIDTH - 200)),
			(int)(100 + (float)(tmp->coord_y - y_min_max[0]) /
			(float)(y_min_max[1] - y_min_max[0]) * (SCREEN_HEIGHT - 200)), fl);
		tmp = tmp->next;
	}
}

static void	draw_lines(int x_min_max[2], int y_min_max[2])
{
	t_room		*tmp;
	t_neighbour	*neighb;

	tmp = g_params->start_of_list;
	while (tmp)
	{
		neighb = tmp->neighbours;
		while (neighb)
		{
			draw_line((int)(100 + (float)(tmp->coord_x - x_min_max[0]) /
				(float)(x_min_max[1] - x_min_max[0]) * (SCREEN_WIDTH - 200)),
				(int)(100 + (float)(tmp->coord_y - y_min_max[0]) /
				(float)(y_min_max[1] - y_min_max[0]) * (SCREEN_HEIGHT - 200)),
				(int)(100 + (float)(neighb->room->coord_x - x_min_max[0]) /
				(float)(x_min_max[1] - x_min_max[0]) * (SCREEN_WIDTH - 200)),
				(int)(100 + (float)(neighb->room->coord_y - y_min_max[0]) /
				(float)(y_min_max[1] - y_min_max[0]) * (SCREEN_HEIGHT - 200)));
			neighb = neighb->next;
		}
		tmp = tmp->next;
	}
}

void	draw_graph(void)
{
	int				x_min_max[2];
	int				y_min_max[2];
	

	arrays_filling(&x_min_max, &y_min_max);
	draw_nodes(x_min_max, y_min_max);
	draw_lines(x_min_max, y_min_max);
}

void	draw_all(void)
{
	int				quit;
	SDL_Event		e;
	SDL_Rect		*r;

	if (!(r = (SDL_Rect *)malloc(sizeof(*r))))
		exit(0);
	r->x = 0;
	r->y = 0;
	r->w = 93;
	r->h = 50;
	draw_graph();
	SDL_RenderCopy(g_params->renderer, g_params->texture, r, r);
	SDL_RenderPresent(g_params->renderer);
	quit = 0;
	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			// printf("The %s key was pressed!\n", SDL_GetKeyName(e.key.keysym.sym));
			// printf("%d, %d\n", e.key.keysym.sym, e.type);
			if ((e.type == KEY_EVENT && e.key.keysym.sym == ESC_KEY) || (e.type == EXIT_CLICK))
			{
				quit = 1;
				break ;
			}
			else if (e.type == KEY_EVENT && e.key.keysym.sym == SPACE_KEY)
			{
				SDL_SetRenderDrawColor(g_params->renderer, 220, 250, 190, 110);
				SDL_RenderClear(g_params->renderer);
				draw_graph();
				SDL_RenderCopy(g_params->renderer, g_params->texture, r, r);
				SDL_RenderPresent(g_params->renderer);
			}
		}
	}
}
