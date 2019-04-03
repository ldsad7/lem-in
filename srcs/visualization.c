/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualization.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:54:47 by bsprigga          #+#    #+#             */
/*   Updated: 2019/04/03 19:37:01 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

SDL_Surface* load_surface(char *filename, SDL_Surface *screen_surface)
{
	//The final optimized image
	SDL_Surface	*optimized_surface;

	optimized_surface = NULL;
	//Load image at specified path
	SDL_Surface	*loaded_surface = IMG_Load(filename);
	if (loaded_surface == NULL)
		ft_printf("Unable to load image %s! SDL_image Error: %s\n", filename, IMG_GetError());
	else
	{
		//Convert surface to screen format
		optimized_surface = SDL_ConvertSurface(loaded_surface, screen_surface->format, 0);
		if(optimized_surface == NULL)
			ft_printf("Unable to optimize image %s! SDL Error: %s\n", filename, SDL_GetError());
		//Get rid of old loaded surface
		SDL_FreeSurface(loaded_surface);
	}
	return (optimized_surface);
}

void	load_media_png(SDL_Surface	*screen_surface, SDL_Window	*window)
{
	SDL_Surface	*ant_png;

	// if (!(ant = SDL_LoadBMP("red_ant.bmp")))
	// 	printf("Unable to load image %s! SDL Error: %s\n", "ant50.bmp", SDL_GetError());

	if (!(ant_png = load_surface("ant50.png", screen_surface)))
		printf("Failed to load PNG image!\n");
	SDL_BlitSurface(ant_png, NULL, screen_surface, NULL);
	

	//Update the surface
	SDL_UpdateWindowSurface(window);
}

void	close_viz(SDL_Window *window, SDL_Surface *screen_surface)
{
    //Deallocate surface
    SDL_FreeSurface(screen_surface);
    screen_surface = NULL;

    //Destroy window
    SDL_DestroyWindow(window);
    window = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

void	init(void)
{
	SDL_Window	*window;
	SDL_Surface	*screen_surface;
	int			img_flags;

	window = NULL;
	screen_surface = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	else
	{
		if (!(window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, 1600, 1200, SDL_WINDOW_SHOWN))) //SCREEN_WIDTH, SCREEN_HEIGHT
			ft_printf(
"Window couldn't be created! SDL_Error: %s\n", SDL_GetError());
		else
		{
			//Initialize PNG loading
			img_flags = IMG_INIT_PNG;
			if (!(IMG_Init(img_flags) & img_flags))
				printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
			else
			{
				//Get window surface
				screen_surface = SDL_GetWindowSurface(window);
			}
		}
	}
	load_media_png(screen_surface, window);
	//Wait twenty seconds
    SDL_Delay(10000);
	close_viz(window, screen_surface);
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
