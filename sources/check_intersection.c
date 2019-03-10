/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 12:42:42 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/07 17:37:48 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	init_ray(t_ray *ray, t_shape *shape, t_rt *rt)
{
	coord_add_subtract(&rt->camera, &shape->center, &ray->a, 1);
	ray->b.x = shape->ray.x;
	ray->b.y = shape->ray.y;
	ray->b.z = shape->ray.z;
	ray->min = 1.0;
	ray->max = INT_MAX;
}

int			check_intersection(t_shape *shape, t_rt *rt)
{
	t_ray	ray;
	double	intersection;

	intersection = INT_MAX;
	init_ray(&ray, shape, rt);
	if (shape->figure == PLANE)
		intersection = plane_intersection(shape, &ray);
	else if (shape->figure == SPHERE)
		intersection = sphere_intersection(shape, &ray);
	else if (shape->figure == CYLINDER)
		intersection = cylinder_intersection(shape, &ray);
	else if (shape->figure == CONE)
		intersection = cone_intersection(shape, &ray);
	if (intersection < rt->t_closest)
	{
		rt->t_closest = intersection;
		return (1);
	}
	return (0);
}
