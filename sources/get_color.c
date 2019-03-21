/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:29:21 by lwyl-the          #+#    #+#             */
/*   Updated: 2019/03/21 20:00:48 by lwyl-the         ###   ########.fr       */
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

int			ft_bmp(t_rt *rt, t_shape *shape)
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
	//printf("%d\n", rt->surf_bmp->format->BytesPerPixel);
	//color = data[x_data * rt->surf_bmp->format->BytesPerPixel + y_data * rt->surf_bmp->pitch];
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
		shape->color = ft_bmp(rt, shape);
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
