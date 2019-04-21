/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives_inf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 15:28:25 by lwyl-the          #+#    #+#             */
/*   Updated: 2019/04/21 13:12:18 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double			gd_infinity_cylinder(t_vec3 *p, t_shape *shape)
{
	t_vec3		orig;

	vec3_subtract(p, &shape->center, &orig);
	vector_matrix_multiply(shape->rotation, &orig);
	return (sqrt(orig.x * orig.x + orig.z * orig.z) - shape->dims.x);
}

double			gd_infinity_cone(t_vec3 *p, t_shape *shape)
{
	t_vec3		orig;
	t_vec3		dimension;
	t_vec3		tmp;
	t_vec3		tmp_1;
	double		distance[3];

	vec3_subtract(p, &shape->center, &orig);
	vector_matrix_multiply(shape->rotation, &orig);
	distance[0] = sqrt(orig.x * orig.x + orig.z * orig.z);
	dimension = (t_vec3) {shape->dims.x, shape->dims.z, 0};
	tmp = (t_vec3) {distance[0], orig.y, 0};
	tmp_1 = (t_vec3) {distance[0], -orig.y, 0};
	vec3_normalize(&dimension, vec3_length(&dimension));
	distance[1] = vec3_dot(&dimension, &tmp);
	distance[2] = vec3_dot(&dimension, &tmp_1);
	distance[1] = unite(distance[1], distance[2]);
	return (distance[1]);
}
