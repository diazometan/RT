/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 14:08:14 by lwyl-the          #+#    #+#             */
/*   Updated: 2019/03/17 17:01:30 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			get_normal_plane(t_shape *shape, t_coord *dir)
{
	shape->normal.x = shape->unit.x;
	shape->normal.y = shape->unit.y;
	shape->normal.z = shape->unit.z;
	if (dot_product(dir, &shape->normal) > 0)
		scalar_product(&shape->normal, -1.0);
}

int	cut_triangle(t_coord *p, t_shape *shape)
{
	t_coord	v[3];
	t_coord	cross_p[3];

	coord_add_subtract(p, &shape->triangle[0], &v[0], 1);
	coord_add_subtract(p, &shape->triangle[2], &v[1], 1);
	coord_add_subtract(p, &shape->triangle[1], &v[2], 1);

	cross_product(&v[0], &shape->abc[0], &cross_p[0]);
	cross_product(&v[1], &shape->abc[1], &cross_p[1]);
	cross_product(&v[2], &shape->abc[2], &cross_p[2]);
	if (dot_product(&cross_p[0], &shape->unit) >= 0 && dot_product(&cross_p[1], &shape->unit) >= 0 && dot_product(&cross_p[2], &shape->unit) >= 0)
		return (1);
	return (0);
}

int			cut_disk(t_coord *p, t_shape *shape)
{
	t_coord	v;

	coord_add_subtract(p, &shape->center, &v, 1);
	if (vector_length(&v) <= shape->radius)
		return (1);
	return (0);
}

double			plane_intersection(t_shape *shape, t_vectors *vectors, t_rt *rt)
{
	double	t;
	double	denominator;
	t_coord	p;

	t = INT_MAX;
	normalize_vector(&shape->unit, vector_length(&shape->unit));
	denominator = dot_product(vectors->dir, &shape->unit);
	if (fabs(denominator) > 0.0001)
	{
		scalar_product(&vectors->orig, -1.0);
		t = dot_product(&vectors->orig, &shape->unit) / denominator;
	}
	if (t > vectors->min && t < vectors->max)
	{
		get_intersection_point(&rt->camera, vectors->dir, t, &p);
		if (shape->figure == PLANE)
			return (t);
		else if (shape->figure == TRIANGLE && cut_triangle(&p, shape))
			return (t);
		else if (shape->figure == DISK && cut_disk(&p, shape))
			return (t);
	}
	return (INT_MAX);
}
