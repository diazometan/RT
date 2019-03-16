/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:29:21 by lwyl-the          #+#    #+#             */
/*   Updated: 2019/03/16 14:00:21 by lwyl-the         ###   ########.fr       */
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

int			get_color(t_shape *shape, t_rt *rt)
{
	int		rgb[3];
	double	light;

	//if (shape->figure != TRIANGLE && shape->figure != DISK)
		//get_intersection_point(&rt->camera, &shape->ray, rt->t_closest, &shape->surface_point);
	get_intersection_point(&rt->camera, &shape->ray, rt->t_closest, &shape->surface_point);
	if (shape->figure == PLANE || shape->figure == TRIANGLE || shape->figure == DISK)
		get_normal_plane(shape);
	else if (shape->figure == SPHERE)
		get_normal_sphere(shape);
	else if (shape->figure == CYLINDER)
		get_normal_cylinder(shape);
	else if (shape->figure == CONE)
		get_normal_cone(shape, shape->angle);
	light = get_light(shape, rt);
	rgb[0] = (shape->color >> 16 & 0xFF) * light;
	rgb[1] = (shape->color >> 8 & 0xFF) * light;
	rgb[2] = (shape->color & 0xFF) * light;
	return (check_color(rgb));
}
