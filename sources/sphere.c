/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 21:10:53 by lwyl-the          #+#    #+#             */
/*   Updated: 2019/03/12 20:44:39 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		get_normal_sphere(t_shape *shape)
{
	coord_add_subtract(&shape->surface_point,
			&shape->center, &shape->normal, 1);
	normalize_vector(&shape->normal, vector_length(&shape->normal));
}

static void	get_sphere_qe_coefficients(t_ray *ray, double radius, t_coef *coef)
{
	double	coef_c;

	coef->a = pow(ray->b.x, 2) + pow(ray->b.y, 2) + pow(ray->b.z, 2);
	coef->b = 2 * dot_product(&ray->a, &ray->b);
	coef_c = pow(ray->a.x, 2) + pow(ray->a.y, 2) +
				pow(ray->a.z, 2) - pow(radius, 2);
	coef->discriminant = pow(coef->b, 2) - 4 * coef->a * coef_c;
}

double		sphere_intersection(t_shape *shape, t_ray *ray)
{
	double	t_1;
	double	t_2;
	double	intersection;
	t_coef	coef;

	intersection = INT_MAX;
	get_sphere_qe_coefficients(ray, shape->radius, &coef);
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
