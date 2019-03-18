/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 12:42:42 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/18 17:18:50 by rgyles           ###   ########.fr       */
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
	vectors->min = 0.0001;
	vectors->max = INT_MAX;
}

int			check_intersection(t_coord *dir, t_shape *shape, t_rt *rt, int depth)
{
	t_vectors	vectors;
	double	intersection;

	intersection = INT_MAX;
	vectors.dir = dir;
	if (depth == rt->depth)
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
