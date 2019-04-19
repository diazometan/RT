/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 10:51:40 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/15 19:12:18 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "kiss_sdl.h"

static int init_sdl(t_sdl *sdl)
{
	SDL_Surface *wall;
	
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("SDL_Init Error: %s\n", SDL_GetError());
		return (1);
	}
	sdl->win = SDL_CreateWindow("RT", 1050, 400, 600, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
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
	wall = SDL_LoadBMP("textures/brick.bmp");
	SDL_BlitScaled(wall, NULL, sdl->surf, NULL);
	SDL_FreeSurface(wall);
	SDL_UpdateWindowSurface(sdl->win);
	sdl->img_data = (int *)sdl->surf->pixels;
	return (0);
}

static char *get_file(int fd)
{
	int error;
	char *line;
	char *file;
	char *tmp;

	file = ft_strnew(1);
	while ((error = get_next_line(fd, &line)) > 0)
	{
		tmp = ft_strjoin(file, ft_strtrim(line));
		free(file);
		file = tmp;
	}
	if (error == -1)
	{
		ft_putendl("gnl error occured");
		free(file);
		exit(1);
	}
	if (ft_strlen(file) == 0)
	{
		ft_putendl("empty file");
		free(file);
		exit(1);
	}
	return (file);
}

void init_rt(t_rt *rt, char *config_file)
{
	int fd;
	char *file;

	rt->head_shapes = NULL;
	rt->head_light = NULL;
	rt->head_textures = NULL;
	rt->p_division = 1;
	//невалидные файлы
	fd = open(config_file, O_RDONLY);
	file = get_file(fd);
	if (init_config(file, rt))
	{
		printf("Error in config file...\n");
		free(file);
		free_args(rt->head_shapes, rt->head_light, rt->head_textures);
		exit(1);
	}
	free(file);
	close(fd);
	rt->sample = 1;
	//create_caps(rt);
	rt->win_width = 600;
	rt->win_height = 600;
}
/* 
void	rt_menu(void)
{
	SDL_Window	*win;
	SDL_Surface	*sur;
	SDL_Color	color_bold;

	win = SDL_CreateWindow("MENU", 700, 100, 500, 600, SDL_WINDOW_SHOWN);
	sur = SDL_GetWindowSurface(win);
	color_bold.r = 0;
	color_bold.g = 255;
	color_bold.b = 0;
	TTF_Init();
	SDL_FillRect(sur, NULL, 0xFAD4CC);
	//draw_title(sur);
	//draw_strings(sur);
	//draw_string("7) Rate of this project can be only above 100.", color_bold, 490, sur);
	SDL_UpdateWindowSurface(win);
	TTF_Quit();
} */

int main(int args, char **argv)
{
	t_rt rt;
	t_sdl sdl;

	srand48(time(NULL));
	if (args != 1)
	{
		ft_putstr("\033[0;31musage: ./RTv1");
		return (1);
	}
	generateNoise();
	//init_rt(&rt, "parser/sph2.json");
	rt.win_width = 0;
	if (init_sdl(&sdl))
		return (1);
	//create_img(&rt, &sdl);
	//rt_menu();

	ui_main(&rt, &sdl);
/* 	while (1)
	{
		SDL_UpdateWindowSurface(sdl.win);
		event_handler(&rt, &sdl);
	} */
	event_handler(&rt, &sdl);
	free_args(rt.head_shapes, rt.head_light, rt.head_textures);
	SDL_DestroyWindow(sdl.win);
	SDL_Quit(); 
}
