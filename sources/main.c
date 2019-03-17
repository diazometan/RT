/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 10:51:40 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/17 19:17:17 by lwyl-the         ###   ########.fr       */
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
	sdl->win = SDL_CreateWindow("RT", 100, 100, 600, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
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
	sdl->img_data = (int *)sdl->surf->pixels;
	return (0);
}

static char	*get_file(int fd)
{
	int		error;
	char	*line;
	char	*file;
	char	*tmp;

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

static void	init_rt(t_rt *rt, char *config_file)
{
	int		fd;
	char	*file;

	rt->head_shapes = NULL;
	rt->head_light = NULL;
	rt->p_division = 1;
	fd = open(config_file, O_RDONLY);
	file = get_file(fd);
	if (init_config(file, rt))
	{
		free(file);
		free_args(rt->head_shapes, rt->head_light);
		exit(1);
	}
	free(file);
	close(fd);
	create_caps(rt);
	rt->win_width = 600;
	rt->win_height = 600;
}

int		main(int args, char **argv)
{
	t_rt	rt;
	t_sdl	sdl;

	if (args != 2)
	{
		ft_putstr("\033[0;31musage: ./RTv1 [configuration_file]\n");
		return (1);
	}
	init_rt(&rt, argv[1]);
	t_shape *h_s = rt.head_shapes;
	t_light *h_l = rt.head_light;
	//TEMPORARY CHECK FOR CONFIG PARSER
	printf("shapes:\n");
	while (h_s != NULL)
	{
		if (h_s->figure == 1)
			printf("plane, ");
		else if (h_s->figure == 2)
			printf("sphere, ");
		else if (h_s->figure == 3)
			printf("cylinder, ");
		else if (h_s->figure == 4)
			printf("cone, ");
		else if (h_s->figure == 5)
			printf("disk, ");
		else if (h_s->figure == 6)
			printf("triangle, ");
		printf("color - %x, specular - %.2f ", h_s->color, h_s->specular);
		if (h_s->figure == SPHERE ||  h_s->figure == CYLINDER || h_s->figure == DISK)
			printf("radius - %.gf ", h_s->radius);
		if (h_s->figure == CONE)
			printf("angle - %.2f ", h_s->angle);
		if (h_s->figure != TRIANGLE)
		{
			printf("\n\tx - %.2f y - %.2f z - %.2f ", h_s->center.x, h_s->center.y, h_s->center.z);
			printf("\n\tx_u - %.2f y_u - %.2f z_u - %.2f ", h_s->unit.x, h_s->unit.y, h_s->unit.z);
		}
		else
		{
			printf("\n\tA: x - %.2f y - %.2f z - %.2f\n", h_s->triangle[0].x, h_s->triangle[0].y, h_s->triangle[0].z);
			printf("\tB: x - %.2f y - %.2f z - %.2f\n", h_s->triangle[1].x, h_s->triangle[1].y, h_s->triangle[1].z);
			printf("\tC: x - %.2f y - %.2f z - %.2f\n", h_s->triangle[2].x, h_s->triangle[2].y, h_s->triangle[2].z);
		}
		printf("\n");
		h_s = h_s->next;
	}
	printf("\nlight sources:\n");
	while (h_l != NULL)
	{
		if (h_l->type == POINT)
			printf("point, ");
		else if (h_l->type == DIRECTIONAL)
			printf("directional, ");
		else if (h_l->type == AMBIENT)
			printf("ambient, ");
		printf("intensity - %.2f ", h_l->intensity);
		if (h_l->type == POINT)
			printf("center x - %.2f y - %.2f z - %.2f", h_l->point.x, h_l->point.y, h_l->point.z);
		else if (h_l->type == DIRECTIONAL)
			printf("direction - x - %.2f y - %.2f z - %.2f", h_l->ray.x, h_l->ray.y, h_l->ray.z);
		h_l = h_l->next;
		printf("\n");
	}
	printf("\ncamera:\n");
	printf("centers at x - %.2f y - %.2f z - %.2f\n", rt.camera.x, rt.camera.y, rt.camera.z);
	printf("looks at x - %.2f y - %.2f z - %.2f\n", rt.angle.x, rt.angle.y, rt.angle.z);
	//END
	(void)sdl;
	if (init_sdl(&sdl))
		return (1);
	create_img(&rt, &sdl);
	//sdl.img_data[300 + rt.win_width * 300] = 0x00FF00;
	SDL_UpdateWindowSurface(sdl.win);
	event_handler(&rt, &sdl);
	free_args(rt.head_shapes, rt.head_light);
	SDL_FreeSurface(sdl.surf);
	SDL_DestroyWindow(sdl.win);
	SDL_Quit();
	return (0);
}
