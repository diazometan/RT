/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 11:29:08 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/21 21:37:05 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				average_color(int n, int *color)
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

void			init_camera_ray(double x, double y, t_vec3 *dir, t_rt *rt)
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

void			get_pixel(int x, int y, t_rt *rt, int *img_data)
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
			get_pixel(x, y, obj->rt, obj->sdl->img_data);
			++obj->rt->count;
		}
	}
	return (NULL);
}

void			create_img(t_rt *rt, t_sdl *sdl)
{
	ft_bzero(sdl->surf->pixels, rt->win_height * rt->win_width * 4);
	draw_borders(rt, sdl);
	sleep(1);
	create_pthread(rt, sdl);
	ft_memcpy(sdl->surf->pixels, (void *)sdl->img_data,
				rt->win_width * rt->win_height * 4);
	SDL_UpdateWindowSurface(sdl->win);
}
