/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 11:24:34 by lwyl-the          #+#    #+#             */
/*   Updated: 2019/03/13 19:43:23 by lwyl-the         ###   ########.fr       */
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

//static double	ray_disk_intersection(t_ray *ray, t_shape *shape, t_rt *rt)
//{
	//double	t;
	//double tmp;
	//t_coord v;
	//t_coord p;
//
	//t = INT_MAX;
	//tmp = plane_intersection(shape, ray);
	//if (tmp != INT_MAX)
	//{
		//p.x = rt->camera.x + tmp * shape->ray.x;
		//p.y = rt->camera.y + tmp * shape->ray.y;
		//p.z = rt->camera.z + tmp * shape->ray.z;
		//v.x = p.x - shape->center.x;
		//v.y = p.y - shape->center.y;
		//v.z = p.z - shape->center.z;
		//t = vector_length(&v);
		//if (t <= 1.5)
			//return (tmp);
		//else
			//return (INT_MAX);
	//}
	//return (t);
//}

double			disk_intersection(t_shape *shape, t_ray *ray, t_rt *rt)
{
	//double	t;
//
	//t = ray_disk_intersection(ray, shape, rt);
	//return (t);
	double	t;
	//double tmp;
	//t_coord v;
	t_coord p;

	t = plane_intersection(shape, ray);
	if (t != INT_MAX)
	{
		p.x = rt->camera.x + t * shape->ray.x;
		p.y = rt->camera.y + t * shape->ray.y;
		p.z = rt->camera.z + t * shape->ray.z;
		coord_add_subtract(&p, &shape->center, &p, 1);
		//v.x = p.x - shape->center.x;
		//v.y = p.y - shape->center.y;
		//v.z = p.z - shape->center.z;
		//t = vector_length(&p);
		if (vector_length(&p) <= shape->radius)
			return (t);
		else
			return (INT_MAX);
	}
	return (INT_MAX);
}
