/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualization.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:54:47 by bsprigga          #+#    #+#             */
/*   Updated: 2019/04/04 16:50:56 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

// SDL_Surface* load_surface(char *filename, SDL_Surface *screen_surface)
// {
// 	//The final optimized image
// 	SDL_Surface	*optimized_surface;
// 	SDL_Surface	*loaded_surface;

// 	optimized_surface = NULL;
// 	//Load image at specified path
// 	loaded_surface = IMG_Load(filename);
// 	if (loaded_surface == NULL)
// 		ft_printf(
// "Unable to load image %s! SDL_image Error: %s\n", filename, IMG_GetError());
// 	else
// 	{
// 		//Convert surface to screen format
// 		optimized_surface = SDL_ConvertSurface(
// 							loaded_surface, screen_surface->format, 0);
// 		if (optimized_surface == NULL)
// 			ft_printf(
// "Unable to optimize image %s! SDL Error: %s\n", filename, SDL_GetError());
// 		//Get rid of old loaded surface
// 		SDL_FreeSurface(loaded_surface);
// 	}
// 	return (optimized_surface);
// }

// void	load_media_png(SDL_Surface *screen_surface, SDL_Window *window)
// {
// 	SDL_Surface	*ant_png;

// 	// if (!(ant = SDL_LoadBMP("red_ant.bmp")))
// 	// 	printf("Unable to load image %s! SDL Error: %s\n", "ant50.bmp", SDL_GetError());

// 	if (!(ant_png = load_surface("ant50.png", screen_surface)))
// 		ft_printf("Failed to load PNG image!\n");
// 	SDL_BlitSurface(ant_png, NULL, screen_surface, NULL);
	

// 	//Update the surface
// 	SDL_UpdateWindowSurface(window);
// 	// window = NULL;
// }

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

SDL_Texture	*load_media_png(SDL_Renderer *renderer)
{
	SDL_Texture *ant_png;

	if (!(ant_png = loadTexture("ant50.png", renderer)))
		ft_printf("Failed to load PNG image!\n");
	//Clear screen
	// SDL_RenderClear(renderer);

	//Render texture to screen
	// SDL_RenderCopy(renderer, ant_png, NULL, NULL);

	// //Update screen
	// SDL_RenderPresent(renderer);
	return (ant_png);
}

// void	close_viz(SDL_Window *window, SDL_Surface *screen_surface)
// {
//     //Deallocate surface
//     SDL_FreeSurface(screen_surface);
//     screen_surface = NULL;

//     //Destroy window
//     SDL_DestroyWindow(window);
//     window = NULL;

//     //Quit SDL subsystems
//     SDL_Quit();
// }

void	draw_circle(SDL_Renderer *renderer, int x, int y)
{
	int				draw_circle_res;

	if ((draw_circle_res = filledCircleRGBA(renderer, x, y, 20, 110, 220, 80, 255)) == -1)
	// if ((draw_circle_res = filledCircleColor(renderer, x, y, 20, 0xFF0000FF)) == -1) //0xAA0000FF
		ft_printf("can't draw circle\n");
}

void	draw_all(SDL_Renderer *renderer)
{
	int				quit;
	SDL_Event		e;
	SDL_Rect		r;
	SDL_Texture		*texture;

	r.x = 0;
	r.y = 0;
	r.w = 50;
	r.h = 50;
	texture = load_media_png(renderer);
	draw_circle(renderer, 100, 100);
	SDL_RenderCopy(renderer, texture, &r, &r);
	SDL_RenderPresent(renderer);
	// //While application is running
	quit = 0;
	while (!quit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
				quit = 1;
			else if (e.type == SDL_KEYUP)
			{
				draw_circle(renderer, 100, 100);
				// fill rectangle with color
				// SDL_RenderFillRect(renderer, &r);
				//Render texture to screen
				SDL_RenderCopy(renderer, texture, &r, &r);
				//Update screen
				SDL_RenderPresent(renderer);
			}
		}
	
	}
}

void	init(void)
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	int				img_flags;

	window = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		ft_printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
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
				ft_printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
		}
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 30, 30, 100, 110);
	//Clear screen
	SDL_RenderClear(renderer);
	draw_all(renderer);
	// close_viz(window, screen_surface);
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
