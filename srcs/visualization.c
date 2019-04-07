/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualization.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:54:47 by bsprigga          #+#    #+#             */
/*   Updated: 2019/04/07 20:48:06 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

SDL_Texture	*loadTexture(char *picture, SDL_Renderer *renderer)
{
    //The final texture
    SDL_Texture	*newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(picture);
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", picture, IMG_GetError());
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", picture, SDL_GetError());
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

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

void	draw_node(SDL_Renderer *renderer, int x, int y, int fl)
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
	if (aacircleRGBA(renderer, x, y, 20, r, g, b, 255) == -1 ||
		filledCircleRGBA(renderer, x, y, 20, r, g, b, 255) == -1)
		exit(ft_printf("can't draw circle\n"));
}

void	draw_line(SDL_Renderer *renderer, int x0, int y0, int x1, int y1)
{
	aalineRGBA(renderer, x0, y0, x1, y1, 0, 0, 255, 255);
}

void	draw_graph(SDL_Renderer *renderer)
{
	t_room			*tmp;
	t_neighbour		*neighb;
	int				x_min_max[2];
	int				y_min_max[2];
	int				fl;

	arrays_filling(&x_min_max, &y_min_max);
	tmp = g_params->start_of_list;
	fl = 0;
	while (tmp)
	{
		if (tmp == g_params->start || tmp == g_params->end)
			fl = 1;
		else
			fl = 0;
		draw_node(renderer, (int)(100 + (float)(tmp->coord_x - x_min_max[0]) /
							(float)(x_min_max[1] - x_min_max[0]) * (SCREEN_WIDTH - 200)),
							(int)(100 + (float)(tmp->coord_y - y_min_max[0]) /
							(float)(y_min_max[1] - y_min_max[0]) * (SCREEN_HEIGHT - 200)), fl);
		tmp = tmp->next;
	}

	tmp = g_params->start_of_list;
	while (tmp)
	{
		neighb = tmp->neighbours;
		while (neighb)
		{
			draw_line(renderer, (int)(100 + (float)(tmp->coord_x - x_min_max[0]) /
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

void	draw_all(SDL_Renderer *renderer, SDL_Texture *texture)
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
	draw_graph(renderer);
	SDL_RenderCopy(renderer, texture, r, r);
	SDL_RenderPresent(renderer);
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
				draw_graph(renderer);
				SDL_RenderCopy(renderer, texture, r, r);
				SDL_RenderPresent(renderer);
			}
		}
	}
}

SDL_Texture	*load_media_png(SDL_Renderer *renderer)
{
	SDL_Texture		*ant_png;

	if (!(ant_png = loadTexture("ant.png", renderer)))
		exit(ft_printf("Failed to load PNG image!\n"));
	return (ant_png);
}

void	close_viz(SDL_Window *window, SDL_Renderer *renderer,
					SDL_Texture *texture)
{
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_DestroyTexture(texture);
	texture = NULL;
	IMG_Quit();
	SDL_Quit();
}

void	init(void)
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;

	window = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		exit(ft_printf("SDL could not initialize! SDL_Error: %s\n",
				SDL_GetError()));
	if (!(window = SDL_CreateWindow("Lem_in", SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN)))
		exit(ft_printf("Window couldn't be created! SDL_Error: %s\n",
														SDL_GetError()));
	if (!(renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)))
		exit(ft_printf(
			"Renderer could not be created! SDL Error: %s\n", SDL_GetError()));
	SDL_SetRenderDrawColor(renderer, 220, 250, 190, 110); // 0xFF, 0xFF, 0xFF, 0xFF
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		exit(ft_printf(
	"SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError()));
	texture = load_media_png(renderer);
	SDL_RenderClear(renderer);
	draw_all(renderer, texture);
	close_viz(window, renderer, texture);
}

void	visualize(int argc, char **argv)
{
	if (argc > 1)
		while (argc-- > 1)
			if (!ft_strcmp(argv[argc], "-v"))
			{
				init();
				break ;
			}
}
