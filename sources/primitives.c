/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 17:49:53 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/02 21:38:39 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double			gd_sphere(t_vec3 *p, t_shape *shape)
{
	t_vec3 orig;

	vec3_subtract(p, &shape->center, &orig);
	vector_matrix_multiply(shape->rotation, &orig);
	return (vec3_length(&orig) - shape->radius);
}

double			gd_plane(t_vec3 *p, t_shape *shape)
{
	t_vec3 orig;

	vec3_subtract(p, &shape->center, &orig);
	//vector_matrix_multiply(shape->rotation, &orig);
	return (vec3_dot(&shape->unit, &orig));
}

double			gd_cylinder(t_vec3 *p, t_shape *shape)
{
	double		m;
	t_vec2		dim;
	t_vec3		orig;

	vec3_subtract(p, &shape->center, &orig);
	vector_matrix_multiply(shape->rotation, &orig);
	dim.x = sqrt(orig.x * orig.x + orig.z * orig.z) - shape->radius;
	dim.y = fabs(orig.y) - shape->h;
	m = ft_dmin(ft_dmax(dim.x, dim.y), 0.0);
	dim.x = dim.x > 0 ? dim.x : 0.0;
	dim.y = dim.y > 0 ? dim.y : 0.0;
	return (m + vec2_length(&dim));
}

double			gd_cone(t_vec3 *p, t_shape *shape)
{
	//NEW
	double		r1 = 1.0;
	double		r2 = 2.0;
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
	k1.y = 2.0 * shape->h;
	coef = ft_dclamp(((r2 - dim.x) * k1.x + (shape->h - dim.y) * k1.y) / (k1.x * k1.x + k1.y + k1.y), 1.0, 0.0);
	k2.x = dim.x - r2 + k1.x * coef;
	k2.y = dim.y - shape->h + k1.y * coef;
	dim.x = dim.x - ft_dmin(dim.x, (dim.y < 0.0) ? r1 : r2);
	dim.y = fabs(dim.y) - shape->h;
	if (k2.x < 0.0 && dim.y < 0.0)
		return ((-1) * sqrt(ft_dmin((dim.x * dim.x + dim.y * dim.y), (k2.x * k2.x + k2.y * k2.y))));
	return (sqrt(ft_dmin((dim.x * dim.x + dim.y * dim.y), (k2.x * k2.x + k2.y * k2.y))));
}

double			gd_capsule(t_vec3 *p, t_shape *shape)
{
	t_vec3 orig;

	vec3_subtract(p, &shape->center, &orig);
	vector_matrix_multiply(shape->rotation, &orig);
	orig.y -= ft_dclamp(orig.y, shape->h, 0.0);
	return (vec3_length(&orig) - shape->radius);
}

double			gd_box(t_vec3 *p, t_shape *shape)
{
	t_vec3 d;
	t_vec3 b;
	t_vec3 orig;
	t_vec3 len;

	vec3_subtract(p, &shape->center, &orig);
	vector_matrix_multiply(shape->rotation, &orig);
	b.x = 1.2;
	b.y = 1.2;
	b.z = 1.2;

	d.x = fabs(orig.x) - b.x;
	d.y = fabs(orig.y) - b.y;
	d.z = fabs(orig.z) - b.z;

	len.x = ft_dmax(d.x, 0.0);
	len.y = ft_dmax(d.y, 0.0);
	len.z = ft_dmax(d.z, 0.0);
	return (vec3_length(&len) - shape->radius + ft_dmin(ft_dmax(d.x, ft_dmax(d.y, d.z)), 0.0));
}
