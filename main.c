/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 19:30:54 by lwyl-the          #+#    #+#             */
/*   Updated: 2019/03/10 16:52:23 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int main()
{
	SDL_Window *win;
	SDL_Renderer *ren;
	SDL_Event event;
	int flag = 0;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("SDL_Init Error: %s\n", SDL_GetError());
		return (1);
	}
	win = SDL_CreateWindow("RT", 100, 100, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	if (win == NULL)
	{
		printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
		return (1);
	}
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == NULL)
	{
		printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
		return (1);
	}
	SDL_RenderClear(ren);
	SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
	SDL_RenderDrawPoint(ren, 300, 300);
	SDL_RenderPresent(ren);
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
		}
	}
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return (0);
}
