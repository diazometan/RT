/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 10:51:40 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/15 10:52:25 by rgyles           ###   ########.fr       */
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

static int	init_rt(t_rt *rt, char *config_file)
{
	int		fd;
	char	*file;

	rt->head_shapes = NULL;
	rt->head_light = NULL;
	rt->head_textures = NULL;
	if ((fd = open(config_file, O_RDONLY)) < 0)
	{
		ft_putendl(M_FILE);
		return (1);
	}
	if ((file = get_file(fd)) == NULL)
		return (1);
	if (init_config(file, rt))
	{
		printf("Error in config file...\n");
		free(file);
		free_args(rt->head_shapes, rt->head_light, rt->head_textures);
		return (1);
	}
	free(file);
	close(fd);
	rt->win_width = 600;
	rt->win_height = 600;
	return (0);
}

int		main(int args, char **argv)
{
	t_rt	rt;
	t_sdl	sdl;

	srand48(time(NULL));
	if (args != 2)
	{
		ft_putendl(USAGE);
		return (1);
	}
	if (init_rt(&rt, argv[1]))
		return (1);
	//TEMPORARY CHECK FOR CONFIG PARSER
	t_shape *h_s = rt.head_shapes;
	t_light *h_l = rt.head_light;
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
		else if (h_s->figure == 7)
			printf("torus, ");
		else if (h_s->figure == 8)
			printf("box, ");
		else if (h_s->figure == 9)
			printf("capsule, ");
		printf("color - %.0f %.0f %.0f, specular - %.2f, reflection = %.2f, refraction - %.2f, emission - %f, ", h_s->color.x, h_s->color.y, h_s->color.z, h_s->specular, h_s->reflection, h_s->refract, h_s->emission);
		if (h_s->texture != NULL)
			printf("texture - %s, ", h_s->texture->name);
		if (h_s->figure == SPHERE ||  h_s->figure == CYLINDER || h_s->figure == DISK || h_s->figure == CONE || h_s->figure == BOX || h_s->figure == CAPSULE)
			printf("radius - %.2f ", h_s->dims.x);
		if (h_s->figure == CYLINDER || h_s->figure == CONE || h_s->figure == CAPSULE)
			printf("height - %.2f ", h_s->dims.y);
		printf("\n\tx - %.2f, y - %.2f, z - %.2f ", h_s->center.x, h_s->center.y, h_s->center.z);
		printf("\n\tx_u - %.2f, y_u - %.2f, z_u - %.2f ", h_s->unit.x, h_s->unit.y, h_s->unit.z);
		printf("\n");
		h_s = h_s->next;
	}
	printf("\nlight sources:\n");
	while (h_l != NULL)
	{
		if (h_l->type == POINT)
			printf("\tpoint, ");
		else if (h_l->type == DIRECTIONAL)
			printf("\tdirectional, ");
		else if (h_l->type == AMBIENT)
			printf("\tambient, ");
		printf("intensity - %.2f, ", h_l->intensity);
		if (h_l->type == POINT)
			printf("center x - %.2f, y - %.2f, z - %.2f", h_l->point.x, h_l->point.y, h_l->point.z);
		else if (h_l->type == DIRECTIONAL)
			printf("direction - x - %.2f, y - %.2f, z - %.2f", h_l->ray.x, h_l->ray.y, h_l->ray.z);
		else if (h_l->type == SPOT)
			printf("direction - x - %.2f, y - %.2f, z - %.2f", h_l->dir.x, h_l->dir.y, h_l->dir.z);
		h_l = h_l->next;
		printf("\n");
	}
	printf("\ncamera:\n");
	printf("\tlocated at x - %.2f, y - %.2f, z - %.2f\n", rt.camera.x, rt.camera.y, rt.camera.z);
	printf("\tlooks at x - %.2f, y - %.2f, z - %.2f\n", rt.angle.x, rt.angle.y, rt.angle.z);
	printf("\nphysics:\n");
	printf("\treflection depth - %d\n", rt.depth);
	printf("\tpixel division - %d\n", rt.p_division);
	//END
	if (init_sdl(&sdl))
		return (1);
	//create_img(&rt, &sdl);
	//event_handler(&rt, &sdl);
	free_args(rt.head_shapes, rt.head_light, rt.head_textures);
	SDL_DestroyWindow(sdl.win);
	SDL_Quit();
	return (0);
}
