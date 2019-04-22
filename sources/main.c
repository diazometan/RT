/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 10:51:40 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/22 20:22:21 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		init_sdl(t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("SDL_Init Error: %s\n", SDL_GetError());
		return (1);
	}
	sdl->win = SDL_CreateWindow("RT", 1050, 400, 600, 600, SDL_WINDOW_SHOWN
				| SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALWAYS_ON_TOP);
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
	sdl->img_data = (int *)check_memory(malloc(sizeof(int) * 600 * 600));
	sdl->pro_data = (int *)sdl->surf->pixels;
	ft_bzero(sdl->surf->pixels, 600 * 600 * 4);
	return (0);
}

void			init_rt_fields(t_rt *rt)
{
	rt->head_shapes = NULL;
	rt->head_light = NULL;
	rt->head_textures = NULL;
	rt->color_scheme = STANDART;
	rt->win_width = 600;
	rt->win_height = 600;
	rt->total_pixels = rt->win_height * rt->win_width;
}

int				init_rt(t_rt *rt, char *config_file)
{
	int			fd;
	char		*file;

	init_rt_fields(rt);
	if ((fd = open(config_file, O_RDONLY)) < 0)
	{
		ft_putendl(M_FILE);
		return (1);
	}
	if ((file = get_file(fd)) == NULL)
		exit(1);
	if (init_config(file, rt))
	{
		printf("Error in config file...\n");
		free(file);
		free_args(rt->head_shapes, rt->head_light, rt->head_textures);
		return (1);
	}
	free(file);
	close(fd);
	return (0);
}

void			window_resized(t_rt *rt, t_sdl *sdl, SDL_Event *event)
{
	SDL_FreeSurface(sdl->surf);
	free(sdl->img_data);
	sdl->surf = SDL_GetWindowSurface(sdl->win);
	rt->win_width = event->window.data1;
	rt->win_height = event->window.data2;
	rt->total_pixels = rt->win_height * rt->win_width;
	sdl->img_data = (int *)check_memory(malloc(sizeof(int) *
						rt->win_width * rt->win_height));
	sdl->pro_data = (int *)sdl->surf->pixels;
	ft_bzero(sdl->surf->pixels, rt->win_width * rt->win_height * 4);
	create_img(rt, sdl);
}

int				main(int args, char **argv)
{
	t_rt		rt;
	t_sdl		sdl;

	if (args > 2)
	{
		ft_putendl(USAGE);
		return (1);
	}
	srand48(time(NULL));
	generate_noise(&rt);
	if (init_sdl(&sdl))
		return (1);
	if (args == 1)
		ui_main(&rt, &sdl);
	else
	{
		if (init_rt(&rt, argv[1]))
			return (1);
		create_img(&rt, &sdl);
	}
	event_handler(&rt, &sdl);
	exit_programm(&rt, &sdl);
	SDL_Quit();
	return (0);
}
