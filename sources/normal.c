/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 10:55:22 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/21 20:11:04 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		create_texute_normal(t_shape *shape, t_rt *rt, t_vec3 tangent,
								t_vec3 bitangent)
{
	t_vec3		normal_from_map;
	t_vec3		normal1;
	t_texture	*temp;

	temp = shape->texture;
	shape->texture = shape->tex_normal;
	normal_from_map = shape->map_texture(shape->tex_normal, shape, rt);
	shape->texture = temp;
	vec3_scalar(&normal_from_map, 1.0 / 255.0);
	normal_from_map.x = 2.0 * normal_from_map.x - 1.0;
	normal_from_map.y = 2.0 * normal_from_map.y - 1.0;
	normal_from_map.z = 2.0 * normal_from_map.z - 1.0;
	vec3_normalize(&normal_from_map, vec3_length(&normal_from_map));
	normal1.x = normal_from_map.x * tangent.x + normal_from_map.y * bitangent.x
				+ normal_from_map.z * rt->normal.x;
	normal1.y = normal_from_map.x * tangent.y + normal_from_map.y * bitangent.y
				+ normal_from_map.z * rt->normal.y;
	normal1.z = normal_from_map.x * tangent.z + normal_from_map.y * bitangent.z
				+ normal_from_map.z * rt->normal.z;
	rt->normal.x = normal1.x;
	rt->normal.y = normal1.y;
	rt->normal.z = normal1.z;
}

void		create_normal_system(t_rt *rt, t_shape *shape)
{
	t_vec3	tangent;
	t_vec3	bitangent;
	t_vec3	unit_1;
	t_vec3	unit_2;
	t_vec3	unit_3;

	unit_1 = (t_vec3) {1, 0, 0};
	unit_2 = (t_vec3) {0, -1, 0};
	unit_3 = (t_vec3) {0, 0, 1};
	vec3_cross(&unit_2, &rt->normal, &tangent);
	if (tangent.x == 0.0 && tangent.y == 0.0 && tangent.z == 0.0)
		vec3_cross(&rt->normal, &unit_1, &tangent);
	else if (tangent.x == 0.0 && tangent.y == 0.0 && tangent.z == 0.0)
		vec3_cross(&rt->normal, &unit_3, &tangent);
	vec3_cross(&rt->normal, &tangent, &bitangent);
	vec3_normalize(&tangent, vec3_length(&tangent));
	vec3_normalize(&bitangent, vec3_length(&bitangent));
	create_texute_normal(shape, rt, tangent, bitangent);
}

void		get_normal(t_vec3 *surface_point, t_vec3 *normal, t_shape *shape)
{
	t_vec3	up;
	t_vec3	down;
	double	delta;

	delta = 10e-5;
	up = (t_vec3) {surface_point->x + delta,
					surface_point->y, surface_point->z};
	down = (t_vec3) {surface_point->x - delta,
					surface_point->y, surface_point->z};
	normal->x = shape_summ(&up, shape) - shape_summ(&down, shape);
	up = (t_vec3) {surface_point->x,
					surface_point->y + delta, surface_point->z};
	down = (t_vec3) {surface_point->x,
					surface_point->y - delta, surface_point->z};
	normal->y = shape_summ(&up, shape) - shape_summ(&down, shape);
	up = (t_vec3) {surface_point->x,
					surface_point->y, surface_point->z + delta};
	down = (t_vec3) {surface_point->x,
					surface_point->y, surface_point->z - delta};
	normal->z = shape_summ(&up, shape) - shape_summ(&down, shape);
	vec3_normalize(normal, vec3_length(normal));
}
