/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 10:40:08 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/08 19:06:47 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			sphere_texture(t_texture *texture, t_shape *shape)
{
	int				x;
	int				y;
	t_vec3			normal;
	unsigned char	*pixel;

	vec3_subtract(&shape->surface_point, &shape->center, &normal);
	vec3_normalize(&normal, vec3_length(&normal));
	x = (0.5 + atan2(normal.z, normal.x) / (2 * M_PI)) * texture->surface->w;
	y = (0.5 - asin(normal.y) / M_PI) * texture->surface->h;
	pixel = texture->pixel + y * texture->surface->pitch + x * texture->surface->format->BytesPerPixel;
	return (*pixel | *(pixel + 1) << 8 | *(pixel + 2) << 16);
}

int			plane_texture(t_texture *texture, t_shape *shape)
{
	int				x;
	int				y;
	double			u;
	double			v;
	unsigned char	*pixel;

	u = shape->surface_point.z;
	v = shape->surface_point.y;
	if (fabs(shape->unit.z) >= fabs(shape->unit.y) && fabs(shape->unit.z) >= fabs(shape->unit.x))
	{
		u = shape->surface_point.x;
		v = shape->surface_point.y;
	}
	else if (fabs(shape->unit.y) >= fabs(shape->unit.x) && fabs(shape->unit.y) >= fabs(shape->unit.z))
	{
		u = shape->surface_point.x;
		v = shape->surface_point.z;
	}
	while (u > 2)
		u -= 2;
	while (u < 0)
		u += 2;
	while (v > 2)
		v -= 2;
	while (v < 0)
		v += 2;
	x = u * texture->surface->w / 2;
	y = (2 - v) * texture->surface->h / 2;
	pixel = texture->pixel + y * texture->surface->pitch + x * texture->surface->format->BytesPerPixel;
	return (*pixel | *(pixel + 1) << 8 | *(pixel + 2) << 16);
}

int			cylinder_texture(t_texture *texture, t_shape *shape)
{
	t_vec3	unit;
	t_vec3	r;
	double	u;
	double	v;
	double tmp;
	int x;
	int y;
	unsigned char	*pixel;
	t_matrix	rotation;

	rotation = matrix_multiply(x_rotation_matrix(shape->unit.x),
								y_rotation_matrix(shape->unit.y));


	unit = shape->unit;
	vec3_normalize(&unit, vec3_length(&unit));
	if (vec3_dot(&unit, &shape->normal) != 0)
		return (sphere_texture(texture, shape));

	//vector_matrix_multiply(rotation, &shape->surface_point);
	vec3_subtract(&shape->surface_point, &shape->center, &r);
	//vec3_normalize(&r, vec3_length(&r));
	u = acos(ft_dclamp(r.x, 1.0, -1.0) / shape->dims.x);
	v = r.y / shape->dims.y;
	//printf("sp = %f   u = %f\n", v, u);
	u = u / M_PI;
	v = (v + 1) / 2;
	x = (1 - u) * texture->surface->w;
	y = (1 - v) * texture->surface->h;
	pixel = texture->pixel + y * texture->surface->pitch + x * texture->surface->format->BytesPerPixel;
	return (*pixel | *(pixel + 1) << 8 | *(pixel + 2) << 16);
}
