/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 10:55:22 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/06 17:57:20 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		get_normal(t_shape *shape)
{
	t_vec3 up;
	t_vec3 down;
	double delta;

	delta = 10e-5;
	up = (t_vec3) {shape->surface_point.x + delta, shape->surface_point.y, shape->surface_point.z};
	down = (t_vec3) {shape->surface_point.x - delta, shape->surface_point.y, shape->surface_point.z};
	// shape->normal.x = shape->gd_fun(&up, shape) - shape->gd_fun(&down, shape);
	shape->normal.x = shape_summ(&up, shape) - shape_summ(&down, shape);

	up = (t_vec3) {shape->surface_point.x, shape->surface_point.y + delta, shape->surface_point.z};
	down = (t_vec3) {shape->surface_point.x, shape->surface_point.y - delta, shape->surface_point.z};
	// shape->normal.y = shape->gd_fun(&up, shape) - shape->gd_fun(&down, shape);
	shape->normal.y = shape_summ(&up, shape) - shape_summ(&down, shape);

	up = (t_vec3) {shape->surface_point.x, shape->surface_point.y, shape->surface_point.z + delta};
	down = (t_vec3) {shape->surface_point.x, shape->surface_point.y, shape->surface_point.z - delta};
	// shape->normal.z = shape->gd_fun(&up, shape) - shape->gd_fun(&down, shape);
	shape->normal.z = shape_summ(&up, shape) - shape_summ(&down, shape);

	vec3_normalize(&shape->normal, vec3_length(&shape->normal));
}
