/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 18:39:58 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/13 12:12:02 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	event_handler(t_rt *rt, t_sdl *sdl)
{
	int			exit;
	SDL_Event	event;

	(void)sdl;
	(void)rt;
	exit = 0;
	while (exit == 0)
	{
		while (SDL_PollEvent(&event))
		{
			SDL_PumpEvents();
			if (event.type == SDL_QUIT)
				exit = 1;
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)
					exit = 1;
			}
			if (event.window.event == SDL_WINDOWEVENT_RESIZED)
			{
				sdl->surf = SDL_GetWindowSurface(sdl->win);
				//data = (int *)surf->pixels;
				//SDL_memset(surf->pixels, 0, surf->h * surf->pitch);
				//data[300 + WIN_WIDTH * 300] = 0xFFFFFF;
				create_img(rt, sdl);
				SDL_UpdateWindowSurface(sdl->win);
			}
		}
	}
}
