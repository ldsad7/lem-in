/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualization_part_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:54:47 by bsprigga          #+#    #+#             */
/*   Updated: 2019/04/09 13:39:37 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

SDL_Texture	*load_texture(char *picture)
{
	SDL_Texture		*new_texture;
	SDL_Surface		*loaded_surface;

	new_texture = NULL;
	loaded_surface = IMG_Load(picture);
	if (!loaded_surface)
		ft_printf("Unable to load image %s! SDL_image Error: %s\n",
		picture, IMG_GetError());
	else
	{
		new_texture = SDL_CreateTextureFromSurface(g_params->renderer,
		loaded_surface);
		if (!new_texture)
			ft_printf("Unable to create texture from %s! SDL Error: %s\n",
			picture, SDL_GetError());
		SDL_FreeSurface(loaded_surface);
	}
	return (new_texture);
}

SDL_Texture	*load_media_png(void)
{
	SDL_Texture		*ant_png;

	if (!(ant_png = load_texture("ant.png")))
		exit(ft_printf("Failed to load PNG image!\n"));
	return (ant_png);
}

void		close_viz(SDL_Window *window)
{
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_DestroyRenderer(g_params->renderer);
	g_params->renderer = NULL;
	SDL_DestroyTexture(g_params->texture);
	g_params->texture = NULL;
	IMG_Quit();
	SDL_Quit();
}

void		init(int nr_steps)
{
	SDL_Window		*window;

	window = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		exit(ft_printf("SDL could not initialize! SDL_Error: %s\n",
				SDL_GetError()));
	if (!(window = SDL_CreateWindow("Lem_in", SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN)))
		exit(ft_printf("Window couldn't be created! SDL_Error: %s\n",
														SDL_GetError()));
	if (!(g_params->renderer = SDL_CreateRenderer(window, -1,
	SDL_RENDERER_ACCELERATED)))
		exit(ft_printf(
			"Renderer could not be created! SDL Error: %s\n", SDL_GetError()));
	SDL_SetRenderDrawColor(g_params->renderer, 220, 250, 190, 110);
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		exit(ft_printf(
	"SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError()));
	g_params->texture = load_media_png();
	SDL_RenderClear(g_params->renderer);
	draw_all(nr_steps);
	close_viz(window);
}

void		visualize(int argc, char **argv, int nr_steps)
{
	if (argc > 1)
		while (argc-- > 1)
			if (!ft_strcmp(argv[argc], "-v"))
			{
				init(nr_steps);
				break ;
			}
}
