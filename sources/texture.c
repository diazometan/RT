/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 10:40:08 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/25 10:56:03 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			sphere_texture(t_shape *shape, t_rt *rt)
{
	int				x;
	int				y;
	t_coord			normal;
	unsigned char	*pixel;

	coord_add_subtract(&shape->surface_point, &shape->center, &normal, 1);
	normalize_vector(&normal, vector_length(&normal));
	x = (0.5 + atan2(normal.z, normal.x) / (2 * M_PI)) * rt->surf_bmp->w;
	y = (0.5 - asin(normal.y) / M_PI) * rt->surf_bmp->h;
	pixel = (unsigned char *)rt->surf_bmp->pixels + y * rt->surf_bmp->pitch + x * 4;
	return (*pixel | *(pixel + 1) << 8 | *(pixel + 2) << 16);
}

int			plane_texture(t_shape *shape, t_rt *rt)
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
	x = u * rt->surf_bmp->w / 2;
	y = (2 - v) * rt->surf_bmp->h / 2;
	pixel = (unsigned char *)rt->surf_bmp->pixels + y * rt->surf_bmp->pitch + x * 4;
	return (*pixel | *(pixel + 1) << 8 | *(pixel + 2) << 16);
}

int			cylinder_texture(t_shape *shape, t_rt *rt)
{
	t_coord op;
	t_coord r;
	double	u;
	double	v;
	int x;
	int y;
	unsigned char	*pixel;

	double	op_l;
	double	om_l;

	r = (t_coord) {1, 0, 0};
	normalize_vector(&r, vector_length(&r));
	coord_add_subtract(&shape->surface_point, &shape->center, &op, 1);
	normalize_vector(&op, (op_l = vector_length(&op)));
	om_l = dot_product(&op, &shape->unit) * op_l;
	//normalize_vector(&normal, vector_length(&normal));
	u = (dot_product(&shape->normal, &r) + 1);
	v = 1 - om_l / shape->h;
	x = u * rt->surf_bmp->w;
	y = v * rt->surf_bmp->h;
	pixel = (unsigned char *)rt->surf_bmp->pixels + y * rt->surf_bmp->pitch + x * 4;
	return (*pixel | *(pixel + 1) << 8 | *(pixel + 2) << 16);
}
