/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 11:24:34 by lwyl-the          #+#    #+#             */
/*   Updated: 2019/03/14 10:49:17 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			get_normal_disk(t_shape *shape)
{
	shape->normal.x = shape->unit.x;
	shape->normal.y = shape->unit.y;
	shape->normal.z = shape->unit.z;
	if (dot_product(&shape->ray, &shape->normal) > 0)
		scalar_product(&shape->normal, -1.0);
}

double			disk_intersection(t_shape *shape, t_ray *ray, t_rt *rt)
{
	double	t;
	t_coord p;

	t = plane_intersection(shape, ray);
	if (t != INT_MAX)
	{
		p.x = rt->camera.x + t * shape->ray.x;
		p.y = rt->camera.y + t * shape->ray.y;
		p.z = rt->camera.z + t * shape->ray.z;
		coord_add_subtract(&p, &shape->center, &p, 1);
		if (vector_length(&p) <= shape->radius)
			return (t);
		else
			return (INT_MAX);
	}
	return (INT_MAX);
}
