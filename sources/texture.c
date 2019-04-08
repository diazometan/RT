/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 10:40:08 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/08 17:53:39 by rgyles           ###   ########.fr       */
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
	double	u;
	double	v;
	int x;
	int y;
	unsigned char	*pixel;


	unit = shape->unit;
	vec3_normalize(&unit, vec3_length(&unit));
	if (vec3_dot(&unit, &shape->normal) != 0)
		return (sphere_texture(texture, shape));
	u = acos(shape->surface_point.x / shape->dims.x);
	v = shape->surface_point.y / shape->dims.y;
	u = (u + 1) / 2;
	v = (v + 1) / 2;
	//printf("v = %f\n", v);
	x = u * texture->surface->w;
	y = v * texture->surface->h;
	pixel = texture->pixel + y * texture->surface->pitch + x * texture->surface->format->BytesPerPixel;
	return (*pixel | *(pixel + 1) << 8 | *(pixel + 2) << 16);
}
