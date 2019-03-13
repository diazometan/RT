/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 17:00:50 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/13 21:06:49 by lwyl-the         ###   ########.fr       */
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

static void	ray_cone_intersection(t_ray *ray, t_shape *shape, t_coef *coef)
{
	double	coef_c;

	coef->scalar_a = dot_product(&ray->b, &shape->unit);
	coef->scalar_b = dot_product(&ray->a, &shape->unit);
	coef->a = (pow((ray->b.x - coef->scalar_a * shape->unit.x), 2) +
			pow((ray->b.y - coef->scalar_a * shape->unit.y), 2) +
			pow((ray->b.z - coef->scalar_a * shape->unit.z), 2)) *
			pow(cos(shape->angle), 2) - pow(sin(shape->angle), 2) *
			pow(coef->scalar_a, 2);
	coef->b = 2 * pow(cos(shape->angle), 2) *
			(((ray->b.x - coef->scalar_a * shape->unit.x) *
			(ray->a.x - coef->scalar_b * shape->unit.x) +
			(ray->b.y - coef->scalar_a * shape->unit.y) *
			(ray->a.y - coef->scalar_b * shape->unit.y) +
			(ray->b.z - coef->scalar_a * shape->unit.z) *
			(ray->a.z - coef->scalar_b * shape->unit.z))) - 2 *
			pow(sin(shape->angle), 2) * coef->scalar_a * coef->scalar_b;
	coef_c = pow(cos(shape->angle), 2) * (pow((ray->a.x - coef->scalar_b *
			shape->unit.x), 2) + pow((ray->a.y - coef->scalar_b *
			shape->unit.y), 2) + pow((ray->a.z - coef->scalar_b *
			shape->unit.z), 2)) - pow(sin(shape->angle), 2) *
			pow(coef->scalar_b, 2);
	coef->discriminant = pow(coef->b, 2) - 4 * coef->a * coef_c;
}

static double		check_cone(t_shape *shape, double t, t_rt *rt)
{
	double tmp;
	t_coord p;

	p.x = rt->camera.x + t * shape->ray.x - shape->center.x;
	p.y = rt->camera.y + t * shape->ray.y - shape->center.y;
	p.z = rt->camera.z + t * shape->ray.z - shape->center.z;
	tmp = dot_product(&p, &shape->unit);
	return (tmp);
}

static double		check_cap(t_shape *shape, t_ray *ray, double t, t_coord top)
{
	double tmp;

	tmp = shape->unit.x * (top.x + ray->b.x * t) + shape->unit.y * (top.y + ray->b.y * t) +
			shape->unit.z * (top.z + ray->b.z * t);
	return (tmp);
}

double		cone_intersection(t_shape *shape, t_ray *ray, t_rt *rt)
{
	double	t_1;
	double	t_2;
	double	intersection;
	t_coef	coef;
	t_coord	top;

	intersection = INT_MAX;
	top.x = rt->camera.x - 0.0;
	top.y = rt->camera.y + 2.0;
	top.z = rt->camera.z - 10.0;
	ray_cone_intersection(ray, shape, &coef);
	normalize_vector(&shape->unit, vector_length(&shape->unit));
	if (coef.discriminant < 0)
		return (INT_MAX);
	t_1 = (-coef.b + sqrt(coef.discriminant)) / (2 * coef.a);
	t_2 = (-coef.b - sqrt(coef.discriminant)) / (2 * coef.a);
	if (t_1 > ray->min && t_1 < ray->max)
		intersection = t_1;
	if (t_2 > ray->min && t_2 < ray->max && t_2 < intersection)
		intersection = t_2;
	if (intersection != INT_MAX)
		if (check_cone(shape, intersection, rt) < 0)
			intersection = INT_MAX;
		if (check_cap(shape,ray, intersection, top) > 0)
			return (INT_MAX);
	return (intersection);
}
