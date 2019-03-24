/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:29:21 by lwyl-the          #+#    #+#             */
/*   Updated: 2019/03/24 18:40:02 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	check_color(int rgb[3])
{
	int	i;
	int	j;
	int	f;
	int	tmp;

	f = 1;
	while (f)
	{
		i = -1;
		f = 0;
		while (++i < 3)
			if (rgb[i] > 255)
			{
				f = 1;
				tmp = rgb[i] - 255;
				rgb[i] = 255;
				j = -1;
				while (++j < 3)
					if (j != i)
						rgb[j] += tmp / 2;
				break ;
			}
	}
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

static int	reflact_color(int color, int refracted_color)
{
	int		rgb_ref[3];
	color = 0;

	rgb_ref[0] = (refracted_color >> 16 & 0xFF);
	rgb_ref[1] = (refracted_color >> 8 & 0xFF);
	rgb_ref[2] = (refracted_color & 0xFF);
	return ((rgb_ref[0] << 16) | (rgb_ref[1] << 8) | rgb_ref[2]);
}

static int	reflect_color(int color, int reflected_color, t_shape *shape)
{
	int		rgb_ref[3];

	rgb_ref[0] = (color >> 16 & 0xFF) * (1 - shape->reflection) +
					(reflected_color >> 16 & 0xFF) * shape->reflection;
	rgb_ref[1] = (color >> 8 & 0xFF) * (1 - shape->reflection) +
					(reflected_color >> 8 & 0xFF) * shape->reflection;
	rgb_ref[2] = (color & 0xFF) * (1 - shape->reflection) +
					(reflected_color & 0xFF) * shape->reflection;
	return ((rgb_ref[0] << 16) | (rgb_ref[1] << 8) | rgb_ref[2]);
}

void		get_normal(t_shape *shape, t_rt *rt, t_coord *dir, int depth)
{
	if (depth == rt->depth)
		get_intersection_point(&rt->camera, dir, rt->t_closest, &shape->surface_point);
	else
		get_intersection_point(rt->source_point, dir, rt->t_closest, &shape->surface_point);
	if (shape->figure == PLANE || shape->figure == TRIANGLE || shape->figure == DISK)
		get_normal_plane(shape, dir);
	else if (shape->figure == SPHERE)
		get_normal_sphere(shape);
	else if (shape->figure == CYLINDER)
		get_normal_cylinder(shape);
	else if (shape->figure == CONE)
		get_normal_cone(shape, shape->angle);
}

int			ft_bmp_sphere(t_rt *rt, t_shape *shape)
{
	t_coord normal;
	double	u;
	double	v;
	int x_data;
	int y_data;
	int color;
	int *data;

	int bpp = rt->surf_bmp->format->BytesPerPixel;
	data = (int*)rt->surf_bmp->pixels;
	coord_add_subtract(&shape->surface_point, &shape->center, &normal, 1);
	normalize_vector(&normal, vector_length(&normal));
	u = 0.5 + atan2(normal.z, normal.x) / (2 * M_PI);
	v = 0.5 - asin(normal.y) / M_PI;
	x_data = u * rt->surf_bmp->w;
	y_data = v * rt->surf_bmp->h;
	Uint8 *p = (Uint8 *)rt->surf_bmp->pixels + y_data * rt->surf_bmp->pitch + x_data * bpp;
	color = (p[0] | p[1] << 8 | p[2] << 16);
	return (color);
}

int			ft_bmp_cylinder(t_rt *rt, t_shape *shape)
{
	t_coord op;
	t_coord r;
	double	u;
	double	v;
	int x_data;
	int y_data;
	int color;

	double	op_l;
	double	om_l;

	r = (t_coord) {1, 0, 0};
	normalize_vector(&r, vector_length(&r));
	coord_add_subtract(&shape->surface_point, &shape->center, &op, 1);
	normalize_vector(&op, (op_l = vector_length(&op)));
	om_l = dot_product(&op, &shape->unit) * op_l;
	int bpp = rt->surf_bmp->format->BytesPerPixel;
	//normalize_vector(&normal, vector_length(&normal));
	u = (dot_product(&shape->normal, &r) + 1);
	v = 1 - om_l / shape->h;
	x_data = u * rt->surf_bmp->w;
	y_data = v * rt->surf_bmp->h;
	Uint8 *p = (Uint8 *)rt->surf_bmp->pixels + y_data * rt->surf_bmp->pitch + x_data * bpp;
	color = (p[0] | p[1] << 8 | p[2] << 16);
	return (color);
}

/*int			ft_bmp_triangle(t_rt *rt, t_shape *shape)
{
	int x_data;
	int y_data;
	int color;
	double bary_a;
	double bary_b;
	double bary_c;
	t_coord tri[3];

	tri[0].x = 1;
	tri[0].y = 2;

	tri[1].x = 1;
	tri[1].y = 0;

	tri[2].x = 3;
	tri[2].y = 0;

	int bpp = rt->surf_bmp->format->BytesPerPixel;

	bary_a = ((tri[1].y - tri[2].y) * (shape->surface_point.x - tri[2].x) +
				(tri[2].x - tri[1].x) * (shape->surface_point.y - tri[2].y))/
				((tri[1].y - tri[2].y) * (tri[0].x - tri[2].x) +
				(tri[2].x - tri[1].x) * (tri[0].y - tri[2].y));
	bary_b = ((tri[2].y - tri[0].y) * (shape->surface_point.x - tri[2].x) +
				(tri[0].x - tri[2].x) * (shape->surface_point.y - tri[2].y))/
				((tri[1].y - tri[2].y) * (tri[0].x - tri[2].x) +
				(tri[2].x - tri[1].x) * (tri[0].y - tri[2].y));
	bary_c = 1 - bary_a - bary_b;

	x_data = bary_c * rt->surf_bmp->w;
	y_data = bary_a * rt->surf_bmp->h;

	Uint8 *p = (Uint8 *)rt->surf_bmp->pixels + y_data * rt->surf_bmp->pitch + x_data * bpp;

	color = (p[0] | p[1] << 8 | p[2] << 16);
	return (color);
}*/

int			ft_bmp_plane(t_rt *rt, t_shape *shape)
{
	int x_data;
	int y_data;
	double u = 0;
	double v = 0;
	int color;

	int bpp = rt->surf_bmp->format->BytesPerPixel;

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

	else //if (fabs(shape->unit.x) >= fabs(shape->unit.y) && fabs(shape->unit.x) >= fabs(shape->unit.z))
	{
		u = shape->surface_point.z;
		v = shape->surface_point.y;
	}

	while (u > 2)
		u -= 2;

	while ( u < 0)
		u += 2;

	while (v > 2)
		v -= 2;

	while ( v < 0)
		v += 2;

	x_data = u * rt->surf_bmp->w / 2;
	y_data = (2 - v) * rt->surf_bmp->h / 2;


	Uint8 *p = (Uint8 *)rt->surf_bmp->pixels + y_data * rt->surf_bmp->pitch + x_data * bpp;

	color = (p[0] | p[1] << 8 | p[2] << 16);
	return (color);
}

int			get_color(t_shape *shape, t_rt *rt, t_coord *dir, int depth)
{
	int		rgb[3];
	double	light;
	int		color = 0;
	int		new_color;

	get_normal(shape, rt, dir, depth);
	rt->source_point = &shape->surface_point;
	light = get_light(shape, rt, dir);
	if (shape->figure == SPHERE)
		shape->color = ft_bmp_sphere(rt, shape);
	if (shape->figure == CYLINDER)
		shape->color = ft_bmp_cylinder(rt, shape);
	if (shape->figure == PLANE || shape->figure == TRIANGLE || shape->figure == DISK)
		shape->color = ft_bmp_plane(rt, shape);
	rgb[0] = (shape->color >> 16 & 0xFF) * light;
	rgb[1] = (shape->color >> 8 & 0xFF) * light;
	rgb[2] = (shape->color & 0xFF) * light;
	color = check_color(rgb);
	if (shape->refract > 0)
	{
		new_color = refraction(dir, shape, rt, depth - 1);
		color = reflact_color(color, new_color);
	}
	if (shape->reflection && depth > 0)
	{
		new_color = reflection(dir, shape, rt, depth - 1);
		color = reflect_color(color, new_color, shape);
	}
	return (color);
}
