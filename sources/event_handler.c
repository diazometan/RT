/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 18:39:58 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/02 13:09:25 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	camera_direction_key(int key, t_rt *rt)
{
	if (key == SDLK_LEFT)
		rt->angle.y += (M_PI * 5.0 / 180);
	else if (key == SDLK_RIGHT)
		rt->angle.y -= (M_PI * 5.0 / 180);
	else if (key == SDLK_UP)
		rt->angle.x += (M_PI * 5.0 / 180);
	else if (key == SDLK_DOWN)
		rt->angle.x -= (M_PI * 5.0 / 180);
	// ADD BUTTONS FOR Z ROTATION
	//else if (key == SDLK_UP)
		//rt->angle.x += (M_PI * 5.0 / 180);
	//else if (key == SDLK_DOWN)
		//rt->angle.x -= (M_PI * 5.0 / 180);
}

static void	camera_position_key(int key, t_rt *rt)
{
	if (key == SDLK_w)
		rt->camera.z += 0.5;
	else if (key == SDLK_s)
		rt->camera.z -= 0.5;
	else if (key == SDLK_d)
		rt->camera.x += 0.5;
	else if (key == SDLK_a)
		rt->camera.x -= 0.5;
	else if (key == SDLK_SPACE)
		rt->camera.y += 0.5;
	else if (key == SDLK_LCTRL)
		rt->camera.y -= 0.5;
}

static void	window_resized(t_rt *rt, t_sdl *sdl, SDL_Event *event)
{
	SDL_FreeSurface(sdl->surf); //DOESNT WORK??? NO LEAKS??? WTF
	sdl->surf = SDL_GetWindowSurface(sdl->win);
	rt->win_width = event->window.data1;
	rt->win_height = event->window.data2;
	sdl->img_data = (int *)sdl->surf->pixels;
	create_img(rt, sdl);
}

void	event_handler(t_rt *rt, t_sdl *sdl)
{
	int			key;
	SDL_Event	event;

	while (1)
	{
		while (SDL_PollEvent(&event))
		{
			SDL_PumpEvents();
			if (event.type == SDL_QUIT)
				return ;
			if (event.type == SDL_KEYDOWN)
			{
				key = event.key.keysym.sym;
				if (key == SDLK_ESCAPE)
					return ;
				else if (key == SDLK_LEFT || key == SDLK_RIGHT || key == SDLK_UP || key == SDLK_DOWN)
					camera_direction_key(key, rt);
				else if (key == SDLK_w || key == SDLK_s || key == SDLK_d ||
							key == SDLK_a || key == SDLK_SPACE || key == SDLK_LCTRL)
					camera_position_key(key, rt);
				else if (key == SDLK_r)
				{
					rt->angle = (t_vec3){0, 0, 0};
					rt->camera = (t_vec3){0, 0, 0};
				}
				create_img(rt, sdl);
			}
			if (event.window.event == SDL_WINDOWEVENT_RESIZED)
				window_resized(rt, sdl, &event);
		}
	}
}
