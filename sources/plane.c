/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 14:08:14 by lwyl-the          #+#    #+#             */
/*   Updated: 2019/03/14 17:59:16 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			get_normal_plane(t_shape *shape)
{
	shape->normal.x = shape->unit.x;
	shape->normal.y = shape->unit.y;
	shape->normal.z = shape->unit.z;
	if (dot_product(&shape->ray, &shape->normal) > 0)
		scalar_product(&shape->normal, -1.0);
}

double	ray_plane_intersection(t_ray *ray, t_shape *shape)
{
	double	t;
	double	denominator;

	t = 0.0;
	normalize_vector(&shape->unit, vector_length(&shape->unit));
	denominator = dot_product(&ray->b, &shape->unit);
	//if (shape->figure == PLANE)
		////printf("x - %f y - %f z - %f\n", shape->unit.x, shape->unit.y, shape->unit.z);
		//printf("den - %f\n", denominator);
	if (fabs(denominator) > 0.0001)
	{
		scalar_product(&ray->a, -1.0);
		t = dot_product(&ray->a, &shape->unit) / denominator;
	}
	return (t);
}

double			plane_intersection(t_shape *shape, t_ray *ray)
{
	double	t;
	double	intersection;

	intersection = INT_MAX;
	t = ray_plane_intersection(ray, shape);
	if (t > ray->min && t < ray->max && t < intersection)
		intersection = t;
	return (intersection);
}
