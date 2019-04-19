/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 11:29:08 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/15 19:09:53 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int average_color(int n, int *color)
{
	int i;
	int n_sq;
	int rgb[3];

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

static void init_camera_ray(double x, double y, t_vec3 *dir, t_rt *rt)
{
	t_matrix rotation;

	rotation = matrix_multiply(x_rotation_matrix(rt->angle.x),
							   y_rotation_matrix(rt->angle.y));
	dir->x = (double)((-rt->win_width / 2) + x) /
				 rt->win_width +
			 rt->camera.x / rt->win_width;
	dir->y = (double)(rt->win_height / 2 - y) /
				 rt->win_height +
			 rt->camera.y / rt->win_height;
	dir->z = 1.0;
	vec3_normalize(dir, vec3_length(dir));
	vector_matrix_multiply(rotation, dir);
	rt->source_point = &rt->camera;
}

int trace_ray(t_vec3 *dir, t_rt *rt, int depth)
{
	t_trace dist;
	t_shape *head;
	t_shape *closest;
	t_vec3 from;

	dist.max_distance = 100;
	dist.epsilon = 10e-6;
	dist.t = 0.0001;
	closest = NULL;
	while (dist.t < dist.max_distance)
	{
		head = rt->head_shapes;
		dist.min_distance = INT_MAX;
		from.x = rt->source_point->x + dist.t * dir->x;
		from.y = rt->source_point->y + dist.t * dir->y;
		from.z = rt->source_point->z + dist.t * dir->z;
		while (head != NULL)
		{
			dist.d = shape_summ(&from, head);
			if (dist.d < dist.min_distance)
			{
				dist.min_distance = dist.d;
				closest = head;
			}
			head = head->next;
		}
		if (dist.min_distance <= dist.epsilon * dist.t)
		{
			rt->t_closest = dist.t;
			return (get_color(dir, closest, rt, depth));
		}
		dist.t += dist.min_distance;
	}
	return (0);
}

static void get_pixel(int x, int y, t_rt *rt, int *img_data)
{
	int i;
	int pixel_color[rt->p_division * rt->p_division];
	double c_x;
	double c_y;
	t_vec3 dir;

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

void create_img(t_rt *rt, t_sdl *sdl)
{
	printf("create_img\n");
	int x;
	int y;
	int x_limit;
	int y_limit;

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
