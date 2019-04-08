/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualization_part_3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:54:47 by bsprigga          #+#    #+#             */
/*   Updated: 2019/04/08 17:38:22 by bsprigga         ###   ########.fr       */
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
