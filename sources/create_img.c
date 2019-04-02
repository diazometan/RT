/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 11:29:08 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/02 21:05:01 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	average_color(int n, int *color)
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

static void	init_camera_ray(double x, double y, t_vec3 *dir, t_rt *rt)
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
}

/*double			get_distance_torus(t_coord *from, t_shape *shape, double r1, double r2)
{
	double tmp_x;
	double tmp_y;
	double distance;
	t_coord tmp;
	t_matrix	rotation;

	rotation = matrix_multiply(inverse_x_rotate(0.5), matrix_multiply(inverse_y_rotate(0.5), inverse_z_rotate(0.5)));

	coord_add_subtract(from, &shape->center, &tmp, 1);
	vector_matrix_multiply(rotation, &tmp);
	tmp_x = sqrt(tmp.x * tmp.x + tmp.y * tmp.y) - r1;
	tmp_y = tmp.z;

	distance = sqrt(tmp_x * tmp_x + tmp_y * tmp_y) - r2;
	return (distance);
}

double			get_distance_cylinder(t_coord *from, t_shape *shape)
{
	t_coord tmp;
	double distance;

	coord_add_subtract(from, &shape->center, &tmp, 1);

	distance = sqrt(tmp.x * tmp.x + tmp.z * tmp.z) - shape->radius;
	return (distance);
}

double			get_distance_cone(t_coord *from, t_shape *shape)
{
	t_coord d;
	t_coord dimension;
	t_coord tmp;
	double len;
	double distance;

	coord_add_subtract(from, &shape->center, &d, 1);
	len = sqrt(d.x * d.x + d.z * d.z);
	dimension.x = 1.0;//shape->radius;
	dimension.y = shape->h;
	dimension.z = 0;

	tmp.x = len;
	tmp.y = d.y;
	tmp.z = 0;
	normalize_vector(&dimension, vector_length(&dimension));
	distance = dot_product(&dimension, &tmp);

	return (distance);
}*/

void		get_normal(t_shape *shape)
{
	t_vec3 tmp_up;
	t_vec3 tmp_down;
	double delta;

	delta = 10e-5;
	tmp_up.x = shape->surface_point.x + delta;
	tmp_down.x = shape->surface_point.x - delta;
	tmp_up.y = shape->surface_point.y;
	tmp_down.y = shape->surface_point.y;
	tmp_up.z = shape->surface_point.z;
	tmp_down.z = shape->surface_point.z;
	shape->normal.x = shape->gd_fun(&tmp_up, shape) - shape->gd_fun(&tmp_down, shape);

	tmp_up.x = shape->surface_point.x;
	tmp_down.x = shape->surface_point.x;
	tmp_up.y = shape->surface_point.y + delta;
	tmp_down.y = shape->surface_point.y - delta;
	tmp_up.z = shape->surface_point.z;
	tmp_down.z = shape->surface_point.z;
	shape->normal.y = shape->gd_fun(&tmp_up, shape) - shape->gd_fun(&tmp_down, shape);

	tmp_up.x = shape->surface_point.x;
	tmp_down.x = shape->surface_point.x;
	tmp_up.y = shape->surface_point.y;
	tmp_down.y = shape->surface_point.y;
	tmp_up.z = shape->surface_point.z + delta;
	tmp_down.z = shape->surface_point.z - delta;
	shape->normal.z = shape->gd_fun(&tmp_up, shape) - shape->gd_fun(&tmp_down, shape);

	vec3_normalize(&shape->normal, vec3_length(&shape->normal));
}

int				trace_ray(t_vec3 *dir, t_rt *rt)
{
	double max_distance;
	double min_distance;
	double epsilon;
	double t;
	double d;
	t_shape *head;
	t_shape	*closest;

	max_distance = 100;
	epsilon = 10e-6;
	t = 0;
	closest = NULL;
	while (t < max_distance)
	{
		head = rt->head_shapes;
		min_distance = INT_MAX;
		t_vec3 from;
		from.x = rt->camera.x + t * dir->x;
		from.y = rt->camera.y + t * dir->y;
		from.z = rt->camera.z + t * dir->z;
		while (head != NULL)
		{
			head->rotation = matrix_multiply(inverse_x_rotate(head->unit.x),
							matrix_multiply(inverse_y_rotate(head->unit.y), inverse_z_rotate(head->unit.z)));
			d = head->gd_fun(&from, head);
			if (d < min_distance)
			{
				min_distance = d;
				closest = head;
			}
			head = head->next;
		}
		if (min_distance <= epsilon * t)
			return (get_color(t, dir, closest, rt));
		t += min_distance;
	}
	return (0);
}

static void		get_pixel(int x, int y, t_rt *rt, int *img_data)
{
	int		i;
	int		pixel_color[rt->p_division * rt->p_division];
	double	c_x;
	double	c_y;
	t_vec3	dir;

	i = -1;
	c_y = y + rt->sample_center;
	while (c_y <= y + 1.0)
	{
		c_x = x + rt->sample_center;
		while (c_x <= x + 1.0)
		{
			init_camera_ray(c_x, c_y, &dir, rt);
			pixel_color[++i] = trace_ray(&dir, rt); //rt->depth);
			c_x += rt->sample_step;
		}
		c_y += rt->sample_step;
	}
	img_data[x + y * rt->win_width] = average_color(rt->p_division, pixel_color);
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
