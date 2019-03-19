/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 17:00:50 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/19 12:21:48 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		get_normal_cone(t_shape *shape, double alpha)
{
	double	h;
	t_coord	op;
	t_coord	ray;

	coord_add_subtract(&shape->surface_point, &shape->center, &op, 1);
	if ((dot_product(&op, &shape->unit) < 0))
		h = (-1) * vector_length(&op) / cos(alpha);
	else
		h = vector_length(&op) / cos(alpha);
	ray.x = shape->unit.x * h;
	ray.y = shape->unit.y * h;
	ray.z = shape->unit.z * h;
	coord_add_subtract(&shape->center, &ray, &ray, 0);
	coord_add_subtract(&shape->surface_point, &ray, &shape->normal, 1);
	normalize_vector(&shape->normal, vector_length(&shape->normal));
}

static void	ray_cone_intersection(t_vectors *vectors, t_shape *shape, t_coef *coef)
{
	double	coef_c;

	coef->scalar_a = dot_product(vectors->dir, &shape->unit);
	coef->scalar_b = dot_product(&vectors->orig, &shape->unit);
	coef->a = (pow((vectors->dir->x - coef->scalar_a * shape->unit.x), 2) +
			pow((vectors->dir->y - coef->scalar_a * shape->unit.y), 2) +
			pow((vectors->dir->z - coef->scalar_a * shape->unit.z), 2)) *
			pow(cos(shape->angle), 2) - pow(sin(shape->angle), 2) *
			pow(coef->scalar_a, 2);
	coef->b = 2 * pow(cos(shape->angle), 2) *
			(((vectors->dir->x - coef->scalar_a * shape->unit.x) *
			(vectors->orig.x - coef->scalar_b * shape->unit.x) +
			(vectors->dir->y - coef->scalar_a * shape->unit.y) *
			(vectors->orig.y - coef->scalar_b * shape->unit.y) +
			(vectors->dir->z - coef->scalar_a * shape->unit.z) *
			(vectors->orig.z - coef->scalar_b * shape->unit.z))) - 2 *
			pow(sin(shape->angle), 2) * coef->scalar_a * coef->scalar_b;
	coef_c = pow(cos(shape->angle), 2) * (pow((vectors->orig.x - coef->scalar_b *
			shape->unit.x), 2) + pow((vectors->orig.y - coef->scalar_b *
			shape->unit.y), 2) + pow((vectors->orig.z - coef->scalar_b *
			shape->unit.z), 2)) - pow(sin(shape->angle), 2) *
			pow(coef->scalar_b, 2);
	coef->discriminant = pow(coef->b, 2) - 4 * coef->a * coef_c;
}

static double		check_cone(t_coord *dir, t_shape *shape, double t, t_rt *rt, int flag)
{
	double tmp;
	t_coord p;

	if (flag == 1)
	{
		p.x = rt->camera.x + t * dir->x - shape->center.x;
		p.y = rt->camera.y + t * dir->y - shape->center.y;
		p.z = rt->camera.z + t * dir->z - shape->center.z;
	}
	else
	{
		p.x = rt->source_point->x + t * dir->x - shape->center.x;
		p.y = rt->source_point->y + t * dir->y - shape->center.y;
		p.z = rt->source_point->z + t * dir->z - shape->center.z;
	}

	tmp = dot_product(&p, &shape->unit);
	return (tmp);
}

static double		check_cap(t_shape *shape, t_vectors *vectors, double t, t_coord top)
{
	double tmp;

	tmp = shape->unit.x * (top.x + vectors->dir->x * t) + shape->unit.y * (top.y + vectors->dir->y * t) +
			shape->unit.z * (top.z + vectors->dir->z * t);
	return (tmp);
}

double		cone_intersection(t_shape *shape, t_vectors *vectors, t_rt *rt)
{
	double	t_1;
	double	t_2;
	double	intersection;
	int flag;
	t_coef	coef;
	t_coord	top;

	intersection = INT_MAX;
	normalize_vector(&shape->unit, vector_length(&shape->unit));
	if (vectors->min == 1.0)
	{
		top.x = rt->camera.x - (shape->center.x + shape->h * shape->unit.x);
		top.y = rt->camera.y - (shape->center.y + shape->h * shape->unit.y);
		top.z = rt->camera.z - (shape->center.z + shape->h * shape->unit.z);
		flag = 1;
	}
	else
	{
		top.x = rt->source_point->x - (shape->center.x + shape->h * shape->unit.x);
		top.y = rt->source_point->y - (shape->center.y + shape->h * shape->unit.y);
		top.z = rt->source_point->z - (shape->center.z + shape->h * shape->unit.z);
		flag = 2;
	}
	ray_cone_intersection(vectors, shape, &coef);
	if (coef.discriminant < 0)
		return (INT_MAX);
	t_1 = (-coef.b + sqrt(coef.discriminant)) / (2 * coef.a);
	t_2 = (-coef.b - sqrt(coef.discriminant)) / (2 * coef.a);
	if (t_1 > vectors->min && t_1 < vectors->max)
		intersection = t_1;
	if (t_2 > vectors->min && t_2 < vectors->max && t_2 < intersection)
		intersection = t_2;
	if (intersection != INT_MAX)
		if (check_cone(vectors->dir, shape, intersection, rt, flag) < 0)
			intersection = INT_MAX;
		if (check_cap(shape,vectors, intersection, top) > 0)
			return (INT_MAX);
	return (intersection);
}
