/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:29:21 by lwyl-the          #+#    #+#             */
/*   Updated: 2019/03/17 19:06:08 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	check_color(int rgb[3])
{
	int	i;
	int	j;
	int	f;
	int	tmp;

	f = 1;
	while (f)
	{
		i = -1;
		f = 0;
		while (++i < 3)
			if (rgb[i] > 255)
			{
				f = 1;
				tmp = rgb[i] - 255;
				rgb[i] = 255;
				j = -1;
				while (++j < 3)
					if (j != i)
						rgb[j] += tmp / 2;
				break ;
			}
	}
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

static void	reflect_ray(t_shape *shape, t_coord *r_v, t_coord *dir)
{
	double	n_dot_r;

	scalar_product(dir, (-1));
	n_dot_r = dot_product(&shape->normal, dir);
	r_v->x = 2 * shape->normal.x * n_dot_r - dir->x;
	r_v->y = 2 * shape->normal.y * n_dot_r - dir->y;
	r_v->z = 2 * shape->normal.z * n_dot_r - dir->z;
}

int		recursion(t_coord *dir, t_shape *shape, t_rt *rt, int depth)
{
	int	reflected_color;
	t_coord r_v;

	reflect_ray(shape, &r_v, dir);
	rt->source_point = &shape->surface_point;
	reflected_color = trace_ray(&r_v, rt, depth);
	return (reflected_color);
}

int		reflect_color(int color, int reflected_color, t_shape *shape)
{
	int		rgb_ref[3];

	rgb_ref[0] = (color >> 16 & 0xFF) * (1 - shape->reflection) +
					(reflected_color >> 16 & 0xFF) * shape->reflection;
	rgb_ref[1] = (color >> 8 & 0xFF) * (1 - shape->reflection) +
					(reflected_color >> 8 & 0xFF) * shape->reflection;
	rgb_ref[2] = (color & 0xFF) * (1 - shape->reflection) +
					(reflected_color & 0xFF) * shape->reflection;
	return ((rgb_ref[0] << 16) | (rgb_ref[1] << 8) | rgb_ref[2]);
}

void		get_normal(t_shape *shape, t_rt *rt, t_coord *dir, int depth)
{
	//if (shape->figure != TRIANGLE && shape->figure != DISK)
		//get_intersection_point(&rt->camera, dir, rt->t_closest, &shape->surface_point);
	if (depth == DEPTH)
		get_intersection_point(&rt->camera, dir, rt->t_closest, &shape->surface_point);
	else
		get_intersection_point(rt->source_point, dir, rt->t_closest, &shape->surface_point);
	if (shape->figure == PLANE || shape->figure == TRIANGLE || shape->figure == DISK)
		get_normal_plane(shape, dir);
	else if (shape->figure == SPHERE)
		get_normal_sphere(shape);
	else if (shape->figure == CYLINDER)
		get_normal_cylinder(shape);
	else if (shape->figure == CONE)
		get_normal_cone(shape, shape->angle);
}

int			get_color(t_shape *shape, t_rt *rt, t_coord *dir, int depth)
{
	int		rgb[3];
	double	light;
	int		color;
	int		reflected_color;

	reflected_color = 0;
	get_normal(shape, rt, dir, depth);
	light = get_light(shape, rt, dir);
	rgb[0] = (shape->color >> 16 & 0xFF) * light;
	rgb[1] = (shape->color >> 8 & 0xFF) * light;
	rgb[2] = (shape->color & 0xFF) * light;
	color = check_color(rgb);
	if (shape->reflection && depth > 0)
	{
		reflected_color = recursion(dir, shape, rt, depth - 1);
		color = reflect_color(color, reflected_color, shape);
	}
	return (color);
}
