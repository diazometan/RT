/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 21:11:30 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/12 20:44:22 by lwyl-the         ###   ########.fr       */
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
	om_l = cos(acos(dot_product(&op, &shape->unit))) * op_l;
	om.x = shape->unit.x * om_l;
	om.y = shape->unit.y * om_l;
	om.z = shape->unit.z * om_l;
	coord_add_subtract(&shape->center, &om, &mp, 0);
	coord_add_subtract(&shape->surface_point, &mp, &shape->normal, 1);
	normalize_vector(&shape->normal, vector_length(&shape->normal));
}

void		ray_cylinder_intersection(t_ray *ray, t_shape *shape, t_coef *coef)
{
	double	coef_c;

	coef->scalar_a = dot_product(&ray->b, &shape->unit);
	coef->scalar_b = dot_product(&ray->a, &shape->unit);
	coef->a = pow((ray->b.x - coef->scalar_a * shape->unit.x), 2) +
			pow((ray->b.y - coef->scalar_a * shape->unit.y), 2) +
			pow((ray->b.z - coef->scalar_a * shape->unit.z), 2);
	coef->b = 2 * ((ray->b.x - coef->scalar_a * shape->unit.x) *
				(ray->a.x - coef->scalar_b * shape->unit.x) +
				(ray->b.y - coef->scalar_a * shape->unit.y) *
				(ray->a.y - coef->scalar_b * shape->unit.y) +
				(ray->b.z - coef->scalar_a * shape->unit.z) *
				(ray->a.z - coef->scalar_b * shape->unit.z));
	coef_c = pow((ray->a.x - coef->scalar_b * shape->unit.x), 2) +
			pow((ray->a.y - coef->scalar_b * shape->unit.y), 2) +
			pow((ray->a.z - coef->scalar_b * shape->unit.z), 2) -
			pow(shape->radius, 2);
	coef->discriminant = pow(coef->b, 2) - 4 * coef->a * coef_c;
}

double		cylinder_intersection(t_shape *shape, t_ray *ray)
{
	double	t_1;
	double	t_2;
	double	intersection;
	t_coef	coef;

	intersection = INT_MAX;
	ray_cylinder_intersection(ray, shape, &coef);
	if (coef.discriminant < 0)
		return (INT_MAX);
	t_1 = (-coef.b + sqrt(coef.discriminant)) / (2 * coef.a);
	t_2 = (-coef.b - sqrt(coef.discriminant)) / (2 * coef.a);
	if (t_1 > ray->min && t_1 < ray->max)
		intersection = t_1;
	if (t_2 > ray->min && t_2 < ray->max && t_2 < intersection)
		intersection = t_2;
	return (intersection);
}
