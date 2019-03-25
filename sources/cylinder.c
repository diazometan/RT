/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 21:11:30 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/25 10:39:55 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		get_normal_cylinder(t_shape *shape)
{
	t_coord	op;
	t_coord	om;
	t_coord	mp;
	double	op_l;
	double	om_l;

	coord_add_subtract(&shape->surface_point, &shape->center, &op, 1);
	normalize_vector(&op, (op_l = vector_length(&op)));
	om_l = dot_product(&op, &shape->unit) * op_l;
	om.x = shape->unit.x * om_l;
	om.y = shape->unit.y * om_l;
	om.z = shape->unit.z * om_l;
	coord_add_subtract(&shape->center, &om, &mp, 0);
	coord_add_subtract(&shape->surface_point, &mp, &shape->normal, 1);
	normalize_vector(&shape->normal, vector_length(&shape->normal));
}

void		ray_cylinder_intersection(t_vectors *vectors, t_shape *shape, t_coef *coef)
{
	double	coef_c;

	coef->scalar_a = dot_product(vectors->dir, &shape->unit);
	coef->scalar_b = dot_product(&vectors->orig, &shape->unit);
	coef->a = pow((vectors->dir->x - coef->scalar_a * shape->unit.x), 2) +
			pow((vectors->dir->y - coef->scalar_a * shape->unit.y), 2) +
			pow((vectors->dir->z - coef->scalar_a * shape->unit.z), 2);
	coef->b = 2 * ((vectors->dir->x - coef->scalar_a * shape->unit.x) *
				(vectors->orig.x - coef->scalar_b * shape->unit.x) +
				(vectors->dir->y - coef->scalar_a * shape->unit.y) *
				(vectors->orig.y - coef->scalar_b * shape->unit.y) +
				(vectors->dir->z - coef->scalar_a * shape->unit.z) *
				(vectors->orig.z - coef->scalar_b * shape->unit.z));
	coef_c = pow((vectors->orig.x - coef->scalar_b * shape->unit.x), 2) +
			pow((vectors->orig.y - coef->scalar_b * shape->unit.y), 2) +
			pow((vectors->orig.z - coef->scalar_b * shape->unit.z), 2) -
			pow(shape->radius, 2);
	coef->discriminant = pow(coef->b, 2) - 4 * coef->a * coef_c;
}

static double check_bot(t_shape *shape, t_vectors *vectors, double t, t_coord *source)
{
	double tmp;

	tmp = shape->unit.x * (source->x + vectors->dir->x * t - shape->center.x) +
			shape->unit.y * (source->y + vectors->dir->y * t - shape->center.y) +
			shape->unit.z * (source->z + vectors->dir->z * t - shape->center.z);
	return (tmp);
}

static double check_top(t_shape *shape, t_vectors *vectors, double t, t_coord *source)
{
	double tmp;
	t_coord	top;

	top.x = shape->center.x + shape->h * shape->unit.x;
	top.y = shape->center.y + shape->h * shape->unit.y;
	top.z = shape->center.z + shape->h * shape->unit.z;
	tmp = shape->unit.x * (source->x + vectors->dir->x * t - top.x) +
			shape->unit.y * (source->y + vectors->dir->y * t - top.y) +
			shape->unit.z * (source->z + vectors->dir->z * t - top.z);
	return (tmp);
}

double		cylinder_intersection(t_shape *shape, t_vectors *vectors, t_rt *rt)
{
	double	t_1;
	double	t_2;
	double	intersection;
	t_coef	coef;
	t_coord *source;

	if (vectors->min == 1.0)
		source = &rt->camera;
	else
		source = rt->source_point;
	intersection = INT_MAX;
	normalize_vector(&shape->unit, vector_length(&shape->unit));
	ray_cylinder_intersection(vectors, shape, &coef);
	if (coef.discriminant < 0)
		return (INT_MAX);
	t_1 = (-coef.b + sqrt(coef.discriminant)) / (2 * coef.a);
	t_2 = (-coef.b - sqrt(coef.discriminant)) / (2 * coef.a);
	if (t_1 > vectors->min && t_1 < vectors->max)
		intersection = t_1;
	if (t_2 > vectors->min && t_2 < vectors->max && t_2 < intersection)
		intersection = t_2;
	if (intersection != INT_MAX && (check_bot(shape, vectors, intersection,source) > 0 &&
					check_top(shape, vectors, intersection, source) < 0))
		return (intersection);
	return (INT_MAX);
}
