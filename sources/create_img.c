/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 11:29:08 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/01 15:11:11 by lwyl-the         ###   ########.fr       */
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

/*int	trace_ray(t_coord *dir, t_rt *rt, int depth)
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
}*/

double			get_distance(t_coord *from, t_shape *shape)
{
	double distance;
	t_coord tmp;

	coord_add_subtract(from, &shape->center, &tmp, 1);
	distance = vector_length(&tmp) - shape->radius;
	return (distance);
}

double			get_distance_plane(t_coord *from, t_shape *shape)
{
	double distance;
	t_coord tmp;

	coord_add_subtract(from, &shape->center, &tmp, 1);
	distance = dot_product(&shape->unit, &tmp);
	return (distance);
}

double			get_distance_torus(t_coord *from, t_shape *shape, double r1, double r2)
{
	double tmp_x;
	double tmp_y;
	double distance;
	t_coord tmp;

	coord_add_subtract(from, &shape->center, &tmp, 1);
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
	//printf("h - %f\n", shape->radius);
	dimension.z = 0;

	tmp.x = len;
	tmp.y = d.y;
	tmp.z = 0;
	normalize_vector(&dimension, vector_length(&dimension));
	//printf("x1 - %f y1 - %f\n", dimension.x, dimension.y);
	distance = dot_product(&dimension, &tmp);

	//printf("dist - %f\n", distance);
	return (distance);
}

int				shadow_sphere(t_coord *orig, t_coord *dir, t_rt *rt, double max_distance)
{
	double min_distance;
	double epsilon;
	double t;
	double d;
	t_coord from;
	t_shape *head;

	t = 0.0;
	epsilon = 10e-5;
	while (t < max_distance)
	{
		head = rt->head_shapes;
		min_distance = INT_MAX;
		from.x = orig->x + t * dir->x;
		from.y = orig->y + t * dir->y;
		from.z = orig->z + t * dir->z;
		while (head != NULL)
		{
			d = get_distance_cone(&from, head);
			if (d < min_distance)
				min_distance = d;
			if (min_distance <= t * epsilon)
				return (0);
			head = head->next;
		}
		t += min_distance;
	}
	return (1);
}

void		normal_for_object(t_shape *shape)
{
	t_coord tmp_up;
	t_coord tmp_down;
	double delta;

	delta = 10e-5;
	tmp_up.x = shape->surface_point.x + delta;
	tmp_down.x = shape->surface_point.x - delta;
	tmp_up.y = shape->surface_point.y;
	tmp_down.y = shape->surface_point.y;
	tmp_up.z = shape->surface_point.z;
	tmp_down.z = shape->surface_point.z;
	shape->normal.x = get_distance_cone(&tmp_up, shape) - get_distance_cone(&tmp_down, shape);

	tmp_up.x = shape->surface_point.x;
	tmp_down.x = shape->surface_point.x;
	tmp_up.y = shape->surface_point.y + delta;
	tmp_down.y = shape->surface_point.y - delta;
	tmp_up.z = shape->surface_point.z;
	tmp_down.z = shape->surface_point.z;
	shape->normal.y = get_distance_cone(&tmp_up, shape) - get_distance_cone(&tmp_down, shape);

	tmp_up.x = shape->surface_point.x;
	tmp_down.x = shape->surface_point.x;
	tmp_up.y = shape->surface_point.y;
	tmp_down.y = shape->surface_point.y;
	tmp_up.z = shape->surface_point.z + delta;
	tmp_down.z = shape->surface_point.z - delta;
	shape->normal.z = get_distance_cone(&tmp_up, shape) - get_distance_cone(&tmp_down, shape);

	normalize_vector(&shape->normal, vector_length(&shape->normal));
}

int			light_sphere(t_shape *shape, t_rt *rt, double t, t_coord *dir)
{

	double dist2;
	double ligth_dot_norm;
	double intens;
	int rgb[3];
	t_coord light;
	t_light *head_light;

	intens = 0.0;
	shape->surface_point.x = rt->camera.x + t * dir->x;
	shape->surface_point.y = rt->camera.y + t * dir->y;
	shape->surface_point.z = rt->camera.z + t * dir->z;

	normal_for_object(shape);

	head_light = rt->head_light;
	while (head_light != NULL)
	{
		light.x = head_light->point.x - shape->surface_point.x;
		light.y = head_light->point.y - shape->surface_point.y;
		light.z = head_light->point.z - shape->surface_point.z;
		ligth_dot_norm = dot_product(&light, &shape->normal);
		if (ligth_dot_norm > 0)
		{
			dist2 = vector_length(&light);
			normalize_vector(&light, dist2);
			if (shadow_sphere(&shape->surface_point, &light, rt, dist2) == 1)
				intens += ligth_dot_norm * head_light->intensity / dist2;
		}
		head_light = head_light->next;
	}
	rgb[0] = (shape->color >> 16 & 0xFF) * intens;
	rgb[1] = (shape->color >> 8 & 0xFF) * intens;
	rgb[2] = (shape->color & 0xFF) * intens;
	return (((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]));
}

int				trace_ray(t_coord *dir, t_rt *rt)
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
		t_coord from;
		from.x = rt->camera.x + t * dir->x;
		from.y = rt->camera.y + t * dir->y;
		from.z = rt->camera.z + t * dir->z;
		while (head != NULL)
		{
			d = get_distance_cone(&from, head);
			if (d < min_distance)
			{
				min_distance = d;
				closest = head;
			}
			head = head->next;
		}
		if (min_distance <= epsilon * t)
			return (light_sphere(closest, rt, t, dir));
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
	t_coord	dir;

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
