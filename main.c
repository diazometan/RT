/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 19:30:54 by lwyl-the          #+#    #+#             */
/*   Updated: 2019/03/10 21:23:56 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int main()
{
	SDL_Window *win;
	SDL_Renderer *ren;
	SDL_Surface *surf;
	SDL_Event event;
	int flag = 0;
	int width;
	int height;
	int *data;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("SDL_Init Error: %s\n", SDL_GetError());
		return (1);
	}
	win = SDL_CreateWindow("RT", 100, 100, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (win == NULL)
	{
		printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
		return (1);
	}
	/*ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == NULL)
	{
		printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
		return (1);
	}*/
	surf = SDL_GetWindowSurface(win);
	if (surf == NULL)
	{
		printf("SDL_GetWindowSurface Error: %s\n", SDL_GetError());
		return (1);
	}
	//SDL_RenderClear(ren);
	//SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
	//SDL_RenderDrawPoint(ren, 300, 300);
	SDL_memset(surf->pixels, 0, surf->h * surf->pitch);
	data = (int *)surf->pixels;
	data[300 + WIN_WIDTH * 300] = 0xFF0000;
	SDL_UpdateWindowSurface(win);
	//SDL_RenderPresent(ren);
	while (!flag)
	{
		while (SDL_PollEvent(&event))
		{
			SDL_PumpEvents();
			if (event.type == SDL_QUIT)
				flag = 1;
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)
					flag = 1;
			}
			if (event.window.event == SDL_WINDOWEVENT_RESIZED)
			{
				surf = SDL_GetWindowSurface(win);
				data = (int *)surf->pixels;
				SDL_memset(surf->pixels, 0, surf->h * surf->pitch);
				data[300 + WIN_WIDTH * 300] = 0xFFFFFF;
				SDL_UpdateWindowSurface(win);
			}
		}
	}
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return (0);
}

