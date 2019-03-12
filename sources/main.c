/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 10:51:40 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/12 15:18:54 by rgyles           ###   ########.fr       */
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

char	*get_file(int fd)
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

void	init_rt(t_rt *rt, char *config_file)
{
	//rt->head_shapes = get_shapes(file_shapes);
	//rt->head_light = get_light_sources(file_light_sources, rt);
	//init_camera(file_camera, rt);
	//rt->canvas = (t_coord) {0.0, 0.0, 1.0};
	int		fd;
	char	*file;

	rt->head_shapes = NULL;
	rt->head_light = NULL;
	fd = open(config_file, O_RDONLY);
	file = get_file(fd);
	printf("%s\n", file);
	if (init_config(file, rt))
	{
		free(file);
		free_args(rt->head_shapes, rt->head_light);
		exit(1);
	}
	//printf("result - %d\n", get_field(file));
	free(file);
	close(fd);
	//return (0);

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
	init_rt(&rt, argv[1]);
	t_shape *h_s = rt.head_shapes;
	t_light *h_l = rt.head_light;
	//TEMPORARY CHECK FOR CONFIG PARSER
	while (h_s != NULL)
	{
		printf("shape - %d color - %x specular - %f ", h_s->figure, h_s->color, h_s->specular);
		if (h_s->figure == SPHERE ||  h_s->figure == CYLINDER)
			printf("radius - %f ", h_s->radius);
		if (h_s->figure != CONE)
			printf("angle - %f ", h_s->angle);
		printf("x - %f y - %f z - %f ", h_s->center.x, h_s->center.y, h_s->center.z);
		printf("x_u - %f y_u - %f z_u - %f ", h_s->unit.x, h_s->unit.y, h_s->unit.z);
		printf("\n\n");
		h_s = h_s->next;
	}
	while (h_l != NULL)
	{
		printf("type - %d intensity - %f ", h_l->type, h_l->intensity);
		if (h_l->type == POINT)
			printf("center x - %f y - %f z - %f", h_l->point.x, h_l->point.y, h_l->point.z);
		else if (h_l->type == DIRECTIONAL)
			printf("direction - x- %f y - %f z - %f", h_l->point.x, h_l->point.y, h_l->point.z);
		h_l = h_l->next;
		printf("\n");
	}
	printf("\ncamera centers at x - %f y - %f z - %f\n", rt.camera.x, rt.camera.y, rt.camera.z);
	printf("camera looks at x - %f y - %f z - %f\n\n", rt.angle.x, rt.angle.y, rt.angle.z);
	printf("\n");
	//END
	(void)sdl;
	//if (init_sdl(&sdl))
		//return (1);
	//create_img(&rt);
	//sdl.img_data[300 + WIN_WIDTH * 300] = 0xFF0000;
	//SDL_UpdateWindowSurface(sdl.win);
	//event_handler(&rt, &sdl);
	//SDL_DestroyWindow(sdl.win);
	//SDL_Quit();
	return (0);
}
