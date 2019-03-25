/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 21:10:53 by lwyl-the          #+#    #+#             */
/*   Updated: 2019/03/25 10:40:45 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		get_normal_sphere(t_shape *shape)
{
	coord_add_subtract(&shape->surface_point,
			&shape->center, &shape->normal, 1);
	normalize_vector(&shape->normal, vector_length(&shape->normal));
}

static void	get_sphere_qe_coefficients(t_vectors *vectors, double radius, t_coef *coef)
{
	double	coef_c;

	coef->a = pow(vectors->dir->x, 2) + pow(vectors->dir->y, 2) + pow(vectors->dir->z, 2);
	coef->b = 2 * dot_product(&vectors->orig, vectors->dir);
	coef_c = pow(vectors->orig.x, 2) + pow(vectors->orig.y, 2) +
				pow(vectors->orig.z, 2) - pow(radius, 2);
	coef->discriminant = pow(coef->b, 2) - 4 * coef->a * coef_c;
}

double		sphere_intersection(t_shape *shape, t_vectors *vectors)
{
	double	t_1;
	double	t_2;
	double	intersection;
	t_coef	coef;

	intersection = INT_MAX;
	get_sphere_qe_coefficients(vectors, shape->radius, &coef);
	if (coef.discriminant < 0)
		return (INT_MAX);
	t_1 = (-coef.b + sqrt(coef.discriminant)) / (2 * coef.a);
	t_2 = (-coef.b - sqrt(coef.discriminant)) / (2 * coef.a);
	if (t_1 > vectors->min && t_1 < vectors->max)
		intersection = t_1;
	if (t_2 > vectors->min && t_2 < vectors->max && t_2 < intersection)
		intersection = t_2;
	return (intersection);
}
