/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 10:51:40 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/11 19:15:54 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		init_sdl(t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("SDL_Init Error: %s\n", SDL_GetError());
		return (1);
	}
	sdl->win = SDL_CreateWindow("RT", 100, 100, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (sdl->win == NULL)
	{
		printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
		return (1);
	}
	sdl->surf = SDL_GetWindowSurface(sdl->win);
	if (sdl->surf == NULL)
	{
		printf("SDL_GetWindowSurface Error: %s\n", SDL_GetError());
		return (1);
	}
	SDL_memset(sdl->surf->pixels, 0, sdl->surf->h * sdl->surf->pitch);
	sdl->img_data = (int *)sdl->surf->pixels;
	SDL_UpdateWindowSurface(sdl->win);
	return (0);
}

void	init_rt(t_rt *rt, char *file_shapes, char *file_light_sources, char *file_camera)
{
	rt->head_shapes = get_shapes(file_shapes);
	rt->head_light = get_light_sources(file_light_sources, rt);
	init_camera(file_camera, rt);
	rt->canvas = (t_coord) {0.0, 0.0, 1.0};
}

int		main(int args, char **argv)
{
	t_rt	rt;
	t_sdl	sdl;

	(void)argv;
	if (args != 2)
	{
		ft_putstr("\033[0;31musage: ./RTv1 [configuration_file]\n");
		return (1);
	}
	//init_rt(&rt, argv[1], argv[2], argv[3]);
	if (init_sdl(&sdl))
		return (1);
	//create_img(&rt);
	sdl.img_data[300 + WIN_WIDTH * 300] = 0xFF0000;
	SDL_UpdateWindowSurface(sdl.win);
	event_handler(&rt, &sdl);
	SDL_DestroyWindow(sdl.win);
	SDL_Quit();
	return (0);
}
