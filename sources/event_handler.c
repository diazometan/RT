/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 18:39:58 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/22 20:26:27 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		camera_direction_key(int key, t_rt *rt)
{
	if (key == SDLK_LEFT)
		rt->angle.y += (M_PI * 5.0 / 180);
	else if (key == SDLK_RIGHT)
		rt->angle.y -= (M_PI * 5.0 / 180);
	else if (key == SDLK_UP)
		rt->angle.x += (M_PI * 5.0 / 180);
	else if (key == SDLK_DOWN)
		rt->angle.x -= (M_PI * 5.0 / 180);
}

static void		camera_position_key(int key, t_rt *rt)
{
	if (key == SDLK_w)
		rt->camera.z += 0.1;
	else if (key == SDLK_s)
		rt->camera.z -= 0.1;
	else if (key == SDLK_d)
		rt->camera.x += 0.1;
	else if (key == SDLK_a)
		rt->camera.x -= 0.1;
	else if (key == SDLK_SPACE)
		rt->camera.y += 0.1;
	else if (key == SDLK_LSHIFT)
		rt->camera.y -= 0.1;
	else if (key == SDLK_r)
	{
		rt->angle = (t_vec3){0, 0, 0};
		rt->camera = (t_vec3){0, 0, 0};
	}
}

static void		color_scheme_key(int key, t_rt *rt)
{
	if (key == SDLK_1)
		rt->color_scheme = STANDART;
	else if (key == SDLK_2)
		rt->color_scheme = INVERSE_ONE;
	else if (key == SDLK_3)
		rt->color_scheme = INVERSE_TWO;
	else if (key == SDLK_4)
		rt->color_scheme = GREY;
	else if (key == SDLK_5)
		rt->color_scheme = CARTOON;
}

static void		key_event(int key, t_rt *rt, t_sdl *sdl)
{
	if (key == SDLK_ESCAPE)
		return ;
	if (key == SDLK_m)
		ui_main(rt, sdl);
	camera_direction_key(key, rt);
	camera_position_key(key, rt);
	color_scheme_key(key, rt);
}

void			event_handler(t_rt *rt, t_sdl *sdl)
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
				key_event(key, rt, sdl);
				if (key != SDLK_m)
					create_img(rt, sdl);
			}
			if (event.window.event == SDL_WINDOWEVENT_RESIZED)
				window_resized(rt, sdl, &event);
		}
	}
}
