/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives_simple.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 17:49:53 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/18 17:12:54 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double			displacement(t_vec3 *p)
{
	double		d;

	d = cos(p->x) + cos(p->y) + cos(p->z);
	return (d);
}

double			gd_sphere(t_vec3 *p, t_shape *shape)
{
	t_vec3		orig;

	vec3_subtract(p, &shape->center, &orig);
	vector_matrix_multiply(shape->rotation, &orig);
	return (vec3_length(&orig) - shape->dims.x);
}

double			gd_plane(t_vec3 *p, t_shape *shape)
{
	t_vec3		orig;
	t_vec3		unit;

	unit = (t_vec3) {0, 1, 0};
	vec3_subtract(p, &shape->center, &orig);
	vector_matrix_multiply(shape->rotation, &orig);
	return fabs(vec3_dot(&unit, &orig));
}

double			gd_cylinder(t_vec3 *p, t_shape *shape)
{
	double		m;
	t_vec2		dim;
	t_vec3		orig;

	vec3_subtract(p, &shape->center, &orig);
	vector_matrix_multiply(shape->rotation, &orig);
	dim.x = sqrt(orig.x * orig.x + orig.z * orig.z) - shape->dims.x;
	dim.y = fabs(orig.y) - shape->dims.y;
	m = ft_dmin(ft_dmax(dim.x, dim.y), 0.0);
	dim.x = dim.x > 0 ? dim.x : 0.0;
	dim.y = dim.y > 0 ? dim.y : 0.0;
	return (m + vec2_length(&dim));
}

double			gd_cone(t_vec3 *p, t_shape *shape)
{
	double		r1 = 0.0;
	double		r2 = 1.0;
	double		coef;
	t_vec2		k1;
	t_vec2		k2;
	t_vec2		dim;
	t_vec3		orig;

	vec3_subtract(p, &shape->center, &orig);
	vector_matrix_multiply(shape->rotation, &orig);
	dim.x = sqrt(orig.x * orig.x + orig.z * orig.z);
	dim.y = -orig.y;
	k1.x = r2 - r1;
	//k1.x = shape->dims.y - shape->dims.x;
	k1.y = 2.0 * shape->dims.y;
	//k1.y = 2.0 * shape->dims.z;
	coef = ft_dclamp(((r2 - dim.x) * k1.x +
				(shape->dims.y - dim.y) * k1.y) / vec2_dot(&k1, &k1), 1.0, 0.0);
	k2.x = dim.x - r2 + k1.x * coef;
	k2.y = dim.y - shape->dims.y + k1.y * coef;
	dim.x = dim.x - ft_dmin(dim.x, (dim.y < 0.0) ?
					r1 : r2);
	dim.y = fabs(dim.y) - shape->dims.y;
	if (k2.x < 0.0 && dim.y < 0.0)
		return ((-1) * sqrt(ft_dmin(vec2_dot(&dim, &dim), vec2_dot(&k2, &k2))));
	return (sqrt(ft_dmin(vec2_dot(&dim, &dim), vec2_dot(&k2, &k2))));
}
