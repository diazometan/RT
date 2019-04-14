/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 10:55:22 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/14 13:42:02 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int TMP = 1;

#include "rt.h"

void		create_texute_normal(t_shape *shape, t_vec3 tangent, t_vec3 bitangent)
{
	t_vec3 normal;
	t_vec3 normal1;

	normal = plane_texture(shape->tex_normal, shape);

	vec3_scalar(&normal, 1.0 / 255.0);
	normal.x = 2.0 * normal.x - 1.0;
	normal.y = 2.0 * normal.y - 1.0;
	normal.z = 2.0 * normal.z - 1.0;
	vec3_normalize(&normal, vec3_length(&normal));
	normal1.x = normal.x * tangent.x + normal.y * bitangent.x + normal.z * shape->normal.x;
	normal1.y = normal.x * tangent.y + normal.y * bitangent.y + normal.z * shape->normal.y;
	normal1.z = normal.x * tangent.z + normal.y * bitangent.z + normal.z * shape->normal.z;
	shape->normal.x = normal1.x;
	shape->normal.y = normal1.y;
	shape->normal.z = normal1.z;
}

void		create_normal_system(t_shape *shape)
{
	t_vec3 tangent;
	t_vec3 bitangent;
	t_vec3 unit_1 = {1, 0, 0};
	t_vec3 unit_2 = {0, 1, 0};
	t_vec3 unit_3 = {0, 0, 1};

	vec3_cross(&shape->normal, &unit_2, &tangent);
	if (tangent.x == 0.0 && tangent.y == 0.0 && tangent.z == 0.0)
		vec3_cross(&shape->normal, &unit_1, &tangent);
	else if (tangent.x == 0.0 && tangent.y == 0.0 && tangent.z == 0.0)
		vec3_cross(&shape->normal, &unit_3, &tangent);
	vec3_cross(&tangent, &shape->normal, &bitangent);

	if (TMP)
	{
		printf("NORMAL %f   %f   %f\n", shape->normal.x, shape->normal.y, shape->normal.z);
		printf("TANGENT %f   %f   %f\n", tangent.x, tangent.y, tangent.z);
		printf("BITANGENT %f   %f   %f\n", bitangent.x, bitangent.y, bitangent.z);
	}
	TMP = 0;

	vec3_normalize(&tangent, vec3_length(&tangent));
	vec3_normalize(&bitangent, vec3_length(&bitangent));
	create_texute_normal(shape, tangent, bitangent);
}

void		get_normal(t_shape *shape)
{
	t_vec3 up;
	t_vec3 down;
	double delta;

	delta = 10e-5;
	up = (t_vec3) {shape->surface_point.x + delta, shape->surface_point.y, shape->surface_point.z};
	down = (t_vec3) {shape->surface_point.x - delta, shape->surface_point.y, shape->surface_point.z};
	shape->normal.x = shape->gd_fun(&up, shape) - shape->gd_fun(&down, shape);

	up = (t_vec3) {shape->surface_point.x, shape->surface_point.y + delta, shape->surface_point.z};
	down = (t_vec3) {shape->surface_point.x, shape->surface_point.y - delta, shape->surface_point.z};
	shape->normal.y = shape->gd_fun(&up, shape) - shape->gd_fun(&down, shape);

	up = (t_vec3) {shape->surface_point.x, shape->surface_point.y, shape->surface_point.z + delta};
	down = (t_vec3) {shape->surface_point.x, shape->surface_point.y, shape->surface_point.z - delta};
	shape->normal.z = shape->gd_fun(&up, shape) - shape->gd_fun(&down, shape);

	vec3_normalize(&shape->normal, vec3_length(&shape->normal));

	if (shape->tex_normal != NULL)
		create_normal_system(shape);
}
