/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:29:21 by lwyl-the          #+#    #+#             */
/*   Updated: 2019/04/19 17:51:56 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	check_color(int rgb[3])
{
	int		i;
	int		j;
	int		f;
	int		tmp;

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

void		standart_color(t_shape *shape, int rgb_m[3], double light)
{
	rgb_m[0] = shape->color.x * light;
	rgb_m[1] = shape->color.y * light;
	rgb_m[2] = shape->color.z * light;
}

void		choose_color(t_rt *rt, t_shape *shape, int rgb[3], double light)
{
	if (rt->color_scheme == STANDART)
		standart_color(shape, rgb, light);
	else if (rt->color_scheme == INVERSE_ONE)
		set_color_invers(shape, rgb, light);
	else if (rt->color_scheme == INVERSE_TWO)
		set_color_invers_hsv(shape, rgb, light);
	else if (rt->color_scheme == GREY)
		set_color_grey(shape, rgb, light);
	else if (rt->color_scheme == CARTOON)
		set_color_cartoon(shape, rgb, light);
}

void		point_and_normal(t_vec3 *dir, t_shape *shape, t_rt *rt)
{
	get_intersection_point(rt->source_point, dir,
							rt->t_closest, &shape->surface_point);
	get_normal(shape);
	if (shape->texture != NULL)
		shape->color = shape->map_texture(shape->texture, shape);
	if (shape->tex_normal != NULL)
		create_normal_system(shape);
}

int			get_color(t_vec3 *dir, t_shape *shape, t_rt *rt, int depth)
{
	int		rgb[3];
	double	light;
	int		color;
	int		new_color;

	point_and_normal(dir, shape, rt);
	light = get_light(dir, shape, rt);
	choose_color(rt, shape, rgb, light);
	color = check_color(rgb);
	if (depth > 0 && shape->reflection)
	{
		new_color = reflection(dir, shape, rt, depth - 1);
		color = reflect_color(color, new_color, shape->reflection);
	}
	if (shape->depth_ref > 0 && shape->refraction)
		color = refraction(dir, shape, rt, shape->depth_ref - 1);
	if (shape->depth_trans > 0 && shape->transparency)
	{
		new_color = transperency(dir, shape, rt, shape->depth_trans - 1);
		color = trans_color(color, new_color, shape->transparency);
	}
	return (color);
}
