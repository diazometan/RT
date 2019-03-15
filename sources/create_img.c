/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 11:29:08 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/15 19:06:25 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	init_camera_ray(double x, double y, t_shape *shape, t_rt *rt)
{
	t_matrix	rotation;

	rotation = matrix_multiply(x_rotation_matrix(rt->angle.x),
								y_rotation_matrix(rt->angle.y));
	shape->ray.x = (double)((-rt->win_width / 2) + x) /
					rt->win_width + rt->camera.x / rt->win_width;
	shape->ray.y = (double)(rt->win_height / 2 - y) /
					rt->win_height + rt->camera.y / rt->win_height;
	shape->ray.z = 1.0;
	normalize_vector(&(shape->ray), vector_length(&shape->ray));
	vector_matrix_multiply(rotation, shape);
}

void		get_pixel(int x, int y, t_rt *rt, t_sdl *sdl, int n)
{
	t_shape	*closest;
	t_shape *shape;
	double	dx = 1.0 / n;
	double	dy = 1.0 / n;
	double	c_x;
	double	c_y;
	int i = 0;
	int j = 0;
	int k = 0;
	int a = 0;
	int		*color;
	int		rgb[3];

	rgb[0] = 0;
	rgb[1] = 0;
	rgb[2] = 0;
	color = (int*)malloc(sizeof(int) * n * n);
	c_y = y + dy / 2.0;
	while (c_y <= (y + 1.0))
	{
		dx = 1.0 / n;
		c_x = x + dx / 2.0;
		while (c_x <= (x + 1.0))
		{
			shape = rt->head_shapes;
			closest = NULL;
			rt->t_closest = INT_MAX;
			while (shape != NULL)
			{
				init_camera_ray(c_x, c_y, shape, rt);
				if (check_intersection(shape, rt))
					closest = shape;
				shape = shape->next;
			}
			if (closest != NULL)
				color[i] = get_color(closest, rt);
			else
				color[i] = 0x0;
			c_x += dx;
			i++;
		}
		c_y += dy;
	}
	while (a < (n * n))
	{
		rgb[0] += ((color[a] >> 16) & 0xFF);
		a++;
	}
	rgb[0] /= (n * n);
	while (j < (n * n))
	{
		rgb[1] += ((color[j] >> 8) & 0xFF);
		j++;
	}
	rgb[1] /= (n * n);
	while (k < (n * n))
	{
		rgb[2] += (color[k] & 0xFF);
		k++;
	}
	rgb[2] /= (n * n);
	sdl->img_data[x + y * rt->win_width] = ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
	free(color);
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
			get_pixel(x, y, rt, sdl, 16);
	}
	SDL_UpdateWindowSurface(sdl->win);
}
