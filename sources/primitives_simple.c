/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives_simple.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 17:49:53 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/17 17:28:31 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double			displacement(t_vec3 *p)
{
	double d;

	d = cos(p->x) + cos(p->y) + cos(p->z);
	return (d);
}

double			gd_sphere(t_vec3 *p, t_shape *shape)
{
	t_vec3 orig;

	vec3_subtract(p, &shape->center, &orig);
	vector_matrix_multiply(shape->rotation, &orig);
	return (vec3_length(&orig) - shape->dims.x);
}

int TMP = 1;
int KEK = 1;

double			gd_plane(t_vec3 *p, t_shape *shape)
{
	t_vec3	orig;
	double	unit1;
	double	unit2;
	t_vec3	tmp;

	vec3_subtract(p, &shape->center, &orig);
	//vector_matrix_multiply(shape->rotation, &orig);
	if (vec3_dot(&shape->unit, &orig) < 0)
	{
		tmp = shape->unit;
		vec3_scalar(&tmp, -1.0);
		return (vec3_dot(&tmp, &orig));
	}
	// unit1 = vec3_dot(&shape->unit, &orig);
	// tmp = shape->unit;
	// vec3_scalar(&tmp, -1.0);
	// unit2 = vec3_dot(&tmp, &orig);
	//if (vec3_dot(&shape->unit, &orig) != fabs(vec3_dot(&shape->unit, &orig)))
	//	printf("%f   %f\n", vec3_dot(&shape->unit, &orig), fabs(vec3_dot(&shape->unit, &orig)));
	//if (fabs(vec3_dot(&shape->unit, &orig)) <= epsilon)
	//	return (0.0);
	return (vec3_dot(&shape->unit, &orig));
	// if (unit1 > -10e-4 && unit1 < 0)
	// 	return (unit1);
	// return (ft_dmax(unit1, unit2));
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
	k2.y = dim.y - r2 + k1.y * coef;
	dim.x = dim.x - ft_dmin(dim.x, (dim.y < 0.0) ?
					r1 : r2);
	dim.y = fabs(dim.y) - r2;
	if (k2.x < 0.0 && dim.y < 0.0)
		return ((-1) * sqrt(ft_dmin(vec2_dot(&dim, &dim), vec2_dot(&k2, &k2))));
	return (sqrt(ft_dmin(vec2_dot(&dim, &dim), vec2_dot(&k2, &k2))));
}
