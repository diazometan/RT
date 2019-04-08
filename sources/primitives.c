/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 17:49:53 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/08 16:11:48 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double			gd_sphere(t_vec3 *p, t_shape *shape)
{
	t_vec3 orig;

	vec3_subtract(p, &shape->center, &orig);
	//vector_matrix_multiply(shape->rotation, &orig);
	return (vec3_length(&orig) - shape->dims.x);
}

double			gd_plane(t_vec3 *p, t_shape *shape)
{
	t_vec3 orig;

	vec3_subtract(p, &shape->center, &orig);
	//vector_matrix_multiply(shape->rotation, &orig);
	return fabs((vec3_dot(&shape->unit, &orig)));
}

double			gd_cylinder(t_vec3 *p, t_shape *shape)
{
	double		m;
	t_vec2		dim;
	t_vec3		orig;

	vec3_subtract(p, &shape->center, &orig);
	//vector_matrix_multiply(shape->rotation, &orig);
	dim.x = sqrt(orig.x * orig.x + orig.z * orig.z) - shape->dims.x;
	dim.y = fabs(orig.y) - shape->dims.y;
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
	//vector_matrix_multiply(shape->rotation, &orig);
	dim.x = sqrt(orig.x * orig.x + orig.z * orig.z);
	dim.y = -orig.y;
	k1.x = r2 - r1;
	k1.y = 2.0 * shape->dims.y;
	coef = ft_dclamp(((r2 - dim.x) * k1.x + (shape->dims.y - dim.y) * k1.y) / vec2_dot(&k1, &k1), 1.0, 0.0);
	k2.x = dim.x - r2 + k1.x * coef;
	k2.y = dim.y - shape->dims.y + k1.y * coef;
	dim.x = dim.x - ft_dmin(dim.x, (dim.y < 0.0) ? r1 : r2);
	dim.y = fabs(dim.y) - shape->dims.y;
	if (k2.x < 0.0 && dim.y < 0.0)
		return ((-1) * sqrt(ft_dmin(vec2_dot(&dim, &dim), vec2_dot(&k2, &k2))));
	return (sqrt(ft_dmin(vec2_dot(&dim, &dim), vec2_dot(&k2, &k2))));
}

double			gd_torus(t_vec3 *p, t_shape *shape)
{
	double		rad;
	t_vec3		orig;
	//t_matrix	rotation;

	//rotation = matrix_multiply(inverse_x_rotate(0.5), matrix_multiply(inverse_y_rotate(0.5), inverse_z_rotate(0.5)));

	vec3_subtract(p, &shape->center, &orig);
	//vector_matrix_multiply(rotation, &tmp);
	rad = sqrt(orig.x * orig.x + orig.y * orig.y) - shape->dims.y;
	return (sqrt(rad * rad + orig.z * orig.z) - shape->dims.x);
}

double			gd_capsule(t_vec3 *p, t_shape *shape)
{
	t_vec3 orig;

	vec3_subtract(p, &shape->center, &orig);
	//vector_matrix_multiply(shape->rotation, &orig);
	orig.y -= ft_dclamp(orig.y, shape->dims.y, 0.0);
	return (vec3_length(&orig) - shape->dims.x);
}

double			gd_box(t_vec3 *p, t_shape *shape)
{
	t_vec3 d;
	t_vec3 orig;
	t_vec3 len;

	vec3_subtract(p, &shape->center, &orig);
	//vector_matrix_multiply(shape->rotation, &orig);
	d.x = fabs(orig.x) - shape->dims.x;
	d.y = fabs(orig.y) - shape->dims.y;
	d.z = fabs(orig.z) - shape->dims.z;
	len.x = ft_dmax(d.x, 0.0);
	len.y = ft_dmax(d.y, 0.0);
	len.z = ft_dmax(d.z, 0.0);
	return (vec3_length(&len) - 0 + ft_dmin(ft_dmax(d.x, ft_dmax(d.y, d.z)), 0.0));
}

/*double			get_distance_cylinder(t_coord *from, t_shape *shape)
{
	t_coord tmp;
	double distance;

	coord_add_subtract(from, &shape->center, &tmp, 1);

	distance = sqrt(tmp.x * tmp.x + tmp.z * tmp.z) - shape->radius;
	return (distance);
}

double			get_distance_cone(t_coord *from, t_shape *shape)
{
	t_coord d;
	t_coord dimension;
	t_coord tmp;
	double len;
	double distance;

	coord_add_subtract(from, &shape->center, &d, 1);
	len = sqrt(d.x * d.x + d.z * d.z);
	dimension.x = 1.0;//shape->radius;
	dimension.y = shape->h;
	dimension.z = 0;

	tmp.x = len;
	tmp.y = d.y;
	tmp.z = 0;
	normalize_vector(&dimension, vector_length(&dimension));
	distance = dot_product(&dimension, &tmp);

	return (distance);
}*/
