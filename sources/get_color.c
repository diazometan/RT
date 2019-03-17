/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:29:21 by lwyl-the          #+#    #+#             */
/*   Updated: 2019/03/17 13:10:00 by rgyles           ###   ########.fr       */
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
	scalar_product(dir, (-1));
	r_v->x = 2 * shape->normal.x * (shape->normal.x * dir->x) - dir->x;
	r_v->y = 2 * shape->normal.y * (shape->normal.y * dir->y) - dir->y;
	r_v->z = 2 * shape->normal.z * (shape->normal.z * dir->z) - dir->z;
}

int		recursion(t_coord *dir, t_shape *shape, t_rt *rt, int depth)
{
	int	reflected_color;
	t_coord r_v;

	reflect_ray(shape, &r_v, dir);
	rt->source_point = &shape->surface_point;
	reflected_color = trace_ray(&r_v, rt, depth, 0);
	return (reflected_color);
}

int			get_color(t_shape *shape, t_rt *rt, t_coord *dir, int depth)
{
	int		rgb[3];
	double	light;
	int		color;
	int		color_red;
	int		color_green;
	int		color_blue;
	int		reflected_color;

	reflected_color = 0;
	//if (shape->figure != TRIANGLE && shape->figure != DISK)
		//get_intersection_point(&rt->camera, &shape->ray, rt->t_closest, &shape->surface_point);
	get_intersection_point(&rt->camera, dir, rt->t_closest, &shape->surface_point);
	if (shape->figure == PLANE || shape->figure == TRIANGLE || shape->figure == DISK)
		get_normal_plane(shape);
	else if (shape->figure == SPHERE)
		get_normal_sphere(shape);
	else if (shape->figure == CYLINDER)
		get_normal_cylinder(shape);
	else if (shape->figure == CONE)
		get_normal_cone(shape, shape->angle);
	light = get_light(shape, rt, dir);
	rgb[0] = (shape->color >> 16 & 0xFF) * light;
	rgb[1] = (shape->color >> 8 & 0xFF) * light;
	rgb[2] = (shape->color & 0xFF) * light;
	color = check_color(rgb);
	if (shape->reflection && depth > 0)
	{
		//printf("check\n");
		reflected_color = recursion(dir, shape, rt, depth - 1);
		color_red = (color >> 16 & 0xFF) * (1 - shape->reflection) + (reflected_color >> 16 & 0xFF) * shape->reflection;
		color_green = (color >> 8 & 0xFF) * (1 - shape->reflection) + (reflected_color >> 8 & 0xFF) * shape->reflection;
		color_blue = (color & 0xFF) * (1 - shape->reflection) + (reflected_color & 0xFF) * shape->reflection;
		color = ((color_red << 16) | (color_green << 8) | color_blue);
	}
	return (color);
}
