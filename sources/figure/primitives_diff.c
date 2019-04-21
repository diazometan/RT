/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives_diff.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 14:59:25 by lwyl-the          #+#    #+#             */
/*   Updated: 2019/04/19 12:41:07 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double			gd_torus(t_vec3 *p, t_shape *shape)
{
	double		rad;
	t_vec3		orig;

	vec3_subtract(p, &shape->center, &orig);
	vector_matrix_multiply(shape->rotation, &orig);
	rad = sqrt(orig.x * orig.x + orig.y * orig.y) - shape->dims.y;
	return (sqrt(rad * rad + orig.z * orig.z) - shape->dims.x);
}

double			gd_capsule(t_vec3 *p, t_shape *shape)
{
	t_vec3 orig;

	vec3_subtract(p, &shape->center, &orig);
	vector_matrix_multiply(shape->rotation, &orig);
	orig.y -= ft_dclamp(orig.y, shape->dims.z, 0.0);
	return (vec3_length(&orig) - shape->dims.x);
}

double			gd_box(t_vec3 *p, t_shape *shape)
{
	t_vec3 d;
	t_vec3 orig;
	t_vec3 len;

	vec3_subtract(p, &shape->center, &orig);
	vector_matrix_multiply(shape->rotation, &orig);
	d.x = fabs(orig.x) - shape->dims.x;
	d.y = fabs(orig.y) - shape->dims.y;
	d.z = fabs(orig.z) - shape->dims.z;
	len.x = ft_dmax(d.x, 0.0);
	len.y = ft_dmax(d.y, 0.0);
	len.z = ft_dmax(d.z, 0.0);
	return (vec3_length(&len) - shape->b_radius +
			ft_dmin(ft_dmax(d.x, ft_dmax(d.y, d.z)), 0.0));
}

double			gd_elispoid(t_vec3 *p, t_shape *shape)
{
	t_vec3 orig;
	t_vec3 tmp;
	t_vec3 tmp_1;
	double k1;
	double k2;

	vec3_subtract(p, &shape->center, &orig);
	vector_matrix_multiply(shape->rotation, &orig);
	tmp.x = orig.x / shape->dims.x;
	tmp.y = orig.y / shape->dims.y;
	tmp.z = orig.z / shape->dims.z;
	k1 = vec3_length(&tmp);
	tmp_1.x = orig.x / (shape->dims.x * shape->dims.x);
	tmp_1.y = orig.y / (shape->dims.y * shape->dims.y);
	tmp_1.z = orig.z / (shape->dims.z * shape->dims.z);
	k2 = vec3_length(&tmp_1);
	return (k1 * (k1 - 1.0) / k2);
}
