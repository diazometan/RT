/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 18:39:58 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/13 18:46:47 by lwyl-the         ###   ########.fr       */
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
				return ;
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)
					return ;
				if (event.key.keysym.sym == SDLK_LEFT)
					rt->angle.y += (M_PI * 5.0 / 180);
				if (event.key.keysym.sym == SDLK_RIGHT)
					rt->angle.y -= (M_PI * 5.0 / 180);
				if (event.key.keysym.sym == SDLK_UP)
					rt->angle.x += (M_PI * 5.0 / 180);
				if (event.key.keysym.sym == SDLK_DOWN)
					rt->angle.x -= (M_PI * 5.0 / 180);
				if (event.key.keysym.sym == SDLK_w)
					rt->camera.z += 0.5;
				if (event.key.keysym.sym == SDLK_s)
					rt->camera.z -= 0.5;
				if (event.key.keysym.sym == SDLK_d)
					rt->camera.x += 0.5;
				if (event.key.keysym.sym == SDLK_a)
					rt->camera.x -= 0.5;
				if (event.key.keysym.sym == SDLK_SPACE)
					rt->camera.y += 0.5;
				if (event.key.keysym.sym == SDLK_LCTRL)
					rt->camera.y -= 0.5;
				if (event.key.keysym.sym == SDLK_r)
				{
					rt->angle = (t_coord){0, 0, 0};
					rt->camera = (t_coord){0, 0, 0};
				}
				create_img(rt, sdl);
				SDL_UpdateWindowSurface(sdl->win);
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
