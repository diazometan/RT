/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 12:42:42 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/16 17:51:11 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	init_ray(t_vectors *vectors, t_shape *shape, t_rt *rt)
{
	coord_add_subtract(&rt->camera, &shape->center, &vectors->orig, 1);
	vectors->min = 1.0;
	vectors->max = INT_MAX;
}

static void	init_ray_reflec(t_vectors *vectors, t_shape *shape, t_rt *rt)
{
	coord_add_subtract(rt->source_point, &shape->center, &vectors->orig, 1);
	vectors->min = 0.001;
	vectors->max = INT_MAX;
}
/*static void	reflect_ray(t_ray *ray, t_shape *shape)
{
	t_coord	ref;

	scalar_product(&ray->b, (-1));
	ray->a.x = shape->surface_point.x;
	ray->a.y = shape->surface_point.y;
	ray->a.z = shape->surface_point.z;
	ray->b.x = 2 * shape->normal.x * dot_product(&shape->normal, &ray->b.x) - ray->b.x;
	ray->b.y = 2 * shape->normal.y * dot_product(&shape->normal, &ray->b.y) - ray->b.y;
	ray->b.z = 2 * shape->normal.z * dot_product(&shape->normal, &ray->b.z) - ray->b.z;
	ray->min = 0.001;
	ray->max = INT_MAX;
}*/

int			check_intersection(t_coord *ray, t_shape *shape, t_rt *rt, int flag)
{
	t_vectors	vectors;
	double	intersection;

	intersection = INT_MAX;
	vectors.dir = ray;
	if (flag == 1)
		init_ray(&vectors, shape, rt);
	else
		init_ray_reflec(&vectors, shape, rt);
	if (shape->figure == PLANE || shape->figure == TRIANGLE || shape->figure == DISK)
		intersection = plane_intersection(shape, &vectors, rt);
	else if (shape->figure == SPHERE)
		intersection = sphere_intersection(shape, &vectors);
	else if (shape->figure == CYLINDER)
		intersection = cylinder_intersection(shape, &vectors, rt);
	else if (shape->figure == CONE)
		intersection = cone_intersection(shape, &vectors, rt);
	if (intersection < rt->t_closest)
	{
		rt->t_closest = intersection;
		return (1);
	}
	return (0);
}
