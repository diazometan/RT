/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 11:29:08 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/21 17:55:02 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		average_color(int n, int *color)
{
	int			i;
	int			n_sq;
	int			rgb[3];

	rgb[0] = 0;
	rgb[1] = 0;
	rgb[2] = 0;
	i = -1;
	n_sq = n * n;
	while (++i < n_sq)
		rgb[0] += ((color[i] >> 16) & 0xFF);
	rgb[0] /= n_sq;
	i = -1;
	while (++i < n_sq)
		rgb[1] += ((color[i] >> 8) & 0xFF);
	rgb[1] /= n_sq;
	i = -1;
	while (++i < n_sq)
		rgb[2] += (color[i] & 0xFF);
	rgb[2] /= n_sq;
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

void		init_camera_ray(double x, double y, t_vec3 *dir, t_rt *rt)
{
	t_matrix	rotation;

	rotation = matrix_multiply(x_rotation_matrix(rt->angle.x),
								y_rotation_matrix(rt->angle.y));
	dir->x = (double)((-rt->win_width / 2) + x) /
					rt->win_width + rt->camera.x / rt->win_width;
	dir->y = (double)(rt->win_height / 2 - y) /
					rt->win_height + rt->camera.y / rt->win_height;
	dir->z = 1.0;
	vec3_normalize(dir, vec3_length(dir));
	vector_matrix_multiply(rotation, dir);
	rt->source_point = rt->camera;
}

void		get_pixel(int x, int y, t_rt *rt, int *img_data)
{
	int			i;
	int			pixel_color[rt->p_division * rt->p_division];
	double		c_x;
	double		c_y;
	t_vec3		dir;

	i = -1;
	c_y = y + rt->sample_center;
	while (c_y <= y + 1.0)
	{
		c_x = x + rt->sample_center;
		while (c_x <= x + 1.0)
		{
			init_camera_ray(c_x, c_y, &dir, rt);
			pixel_color[++i] = trace_ray(&dir, rt, rt->depth);
			c_x += rt->sample_step;
		}
		c_y += rt->sample_step;
	}
	img_data[x + y * rt->win_width] =
					average_color(rt->p_division, pixel_color);
}

void			*create_img_pthread(void *data)
{
	int			x;
	int			y;
	int			x_limit;
	int			y_limit;
	t_pthread	*obj;

	obj = (t_pthread *)data;
	x_limit = obj->x[1];
	y_limit = obj->y[1];
	y = obj->y[0] - 1;
	while (++y < y_limit)
	{
		x = obj->x[0] - 1;
		while (++x < x_limit)
		{
			// printf("x(%d %d) y(%d %d) x=%d y=%d\n", obj->x[0], x_limit, obj->y[0], y_limit, x, y);
			get_pixel(x, y, obj->rt, obj->sdl->img_data);
		}
	}
	return (NULL);
}

t_pthread	init_t_pthread(t_rt *rt, t_sdl *sdl, int x[2], int y[2])
{
	t_pthread	obj;

	obj.rt = rt;
	obj.sdl = sdl;
	obj.x[0] = x[0];
	obj.x[1] = x[1];
	obj.y[0] = y[0];
	obj.y[1] = y[1];
	return (obj);
}

void		ft_fun(t_rt *rt, t_sdl *sdl)
{
	int					size;
	int					index;
	pthread_t			*tid;
	t_pthread			*blocks;
	int					start;
	int					finish;
	t_rt				*new_rts;

	size = 8;
	tid = (pthread_t *)malloc(sizeof(pthread_t) * size);
	blocks = (t_pthread *)malloc(sizeof(t_pthread) * size);
	new_rts = (t_rt *)malloc(sizeof(t_rt) * size);
	index = -1;
	while (++index < size)
	{
		start = ((index) / (double)size) * rt->win_width;
		finish = ((index + 1) / (double)size) * rt->win_width;
		new_rts[index] = *rt;
		blocks[index] = init_t_pthread(&(new_rts[index]), sdl,
		(int[2]){start, finish},
		(int[2]){0, rt->win_height});
		(void)pthread_create(&tid[index], NULL, create_img_pthread, &blocks[index]);
	}
	index = -1;
	while (++index < size)
		pthread_join(tid[index], NULL);
	index = -1;
	free(tid);
	free(blocks);
	free(new_rts);
}

void			create_img(t_rt *rt, t_sdl *sdl)
{
	// t_pthread	obj;

	ft_bzero(sdl->surf->pixels, rt->win_height * rt->win_width * 4);
	// obj = init_t_pthread(rt, sdl, (int[2]){0, rt->win_width}, (int[2]){0, rt->win_height});
	// create_img_pthread(&obj);
	ft_fun(rt, sdl);
	SDL_UpdateWindowSurface(sdl->win);
	// exit(0);
}
