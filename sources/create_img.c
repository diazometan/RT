/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 11:29:08 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/17 17:24:54 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	average_color(int n, int *color)
{
	int i;
	int rgb[3];

	rgb[0] = 0;
	rgb[1] = 0;
	rgb[2] = 0;
	i = -1;
	while (++i < n * n)
		rgb[0] += ((color[i] >> 16) & 0xFF);
	rgb[0] /= n * n;
	i = -1;
	while (++i < n * n)
		rgb[1] += ((color[i] >> 8) & 0xFF);
	rgb[1] /= n * n;
	i = -1;
	while (++i < n * n)
		rgb[2] += (color[i] & 0xFF);
	rgb[2] /= n * n;
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

static void	init_camera_ray(double x, double y, t_coord *dir, t_rt *rt)
{
	t_matrix	rotation;

	rotation = matrix_multiply(x_rotation_matrix(rt->angle.x),
								y_rotation_matrix(rt->angle.y));
	dir->x = (double)((-rt->win_width / 2) + x) /
					rt->win_width + rt->camera.x / rt->win_width;
	dir->y = (double)(rt->win_height / 2 - y) /
					rt->win_height + rt->camera.y / rt->win_height;
	dir->z = 1.0;
	normalize_vector(dir, vector_length(dir));
	vector_matrix_multiply(rotation, dir);
}

int	trace_ray(t_coord *dir, t_rt *rt, int depth)
{
	t_shape	*closest;
	t_shape	*shape;

	shape = rt->head_shapes;
	closest = NULL;
	rt->t_closest = INT_MAX;
	while (shape != NULL)
	{
		if (check_intersection(dir, shape, rt, depth))
			closest = shape;
		shape = shape->next;
	}
	if (closest != NULL)
		return (get_color(closest, rt, dir, depth));
	return (0);
}

static void		get_pixel(int x, int y, t_rt *rt, int *img_data)
{
	t_coord	dir;
	t_pixel	pixel;

	pixel.i = 0;
	pixel.dx = 1.0 / rt->sample;
	pixel.dy = 1.0 / rt->sample;
	pixel.color = (int *)malloc(sizeof(int) * rt->sample * rt->sample);
	pixel.c_y = y + pixel.dy / 2.0;
	while (pixel.c_y <= y + 1.0)
	{
		pixel.dx = 1.0 / rt->sample;
		pixel.c_x = x + pixel.dx / 2.0;
		while (pixel.c_x <= x + 1.0)
		{
			init_camera_ray(pixel.c_x, pixel.c_y, &dir, rt);
			pixel.color[pixel.i] = trace_ray(&dir, rt, DEPTH);
			pixel.c_x += pixel.dx;
			++pixel.i;
		}
		pixel.c_y += pixel.dy;
	}
	img_data[x + y * rt->win_width] = average_color(rt->sample, pixel.color);
	free(pixel.color);
}

void		create_img(t_rt *rt, t_sdl *sdl)
{
	int		x;
	int		y;
	int		x_limit;
	int		y_limit;

	y = -1;
	x_limit = rt->win_width;
	y_limit = rt->win_height;
	while (++y < y_limit)
	{
		x = -1;
		while (++x < x_limit)
			get_pixel(x, y, rt, sdl->img_data);
	}
	SDL_UpdateWindowSurface(sdl->win);
}
