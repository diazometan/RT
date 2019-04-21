/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:29:21 by lwyl-the          #+#    #+#             */
/*   Updated: 2019/04/21 14:39:39 by lwyl-the         ###   ########.fr       */
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

void		standart_color(t_rt *rt, int rgb_m[3], double light)
{
	rgb_m[0] = rt->color.x * light;
	rgb_m[1] = rt->color.y * light;
	rgb_m[2] = rt->color.z * light;
}

void		choose_color(t_rt *rt, int rgb[3], double light)
{
	if (rt->color_scheme == STANDART)
		standart_color(rt, rgb, light);
	else if (rt->color_scheme == INVERSE_ONE)
		set_color_invers(rt, rgb, light);
	else if (rt->color_scheme == INVERSE_TWO)
		set_color_invers_hsv(rt, rgb, light);
	else if (rt->color_scheme == GREY)
		set_color_grey(rt, rgb, light);
	else if (rt->color_scheme == CARTOON)
		set_color_cartoon(rt, rgb, light);
}

void		point_and_normal(t_vec3 *dir, t_shape *shape, t_rt *rt)
{
	get_intersection_point(&rt->source_point, dir,
							rt->t_closest, &rt->source_point);
	get_normal(&rt->source_point, &rt->normal, shape);
	if (shape->texture != NULL)
		rt->color = shape->map_texture(shape->texture, shape, rt);
	else
		rt->color = shape->color;
	if (shape->tex_normal != NULL)
		create_normal_system(rt, shape);
}

int			get_color(t_vec3 *dir, t_shape *shape, t_rt *rt, int depth)
{
	int		rgb[3];
	double	light;
	int		color;
	int		new_color;

	point_and_normal(dir, shape, rt);
	light = get_light(dir, shape, rt);
	choose_color(rt, rgb, light);
	color = check_color(rgb);
	if (depth > 0 && shape->reflection)
	{
		new_color = reflection(dir, rt, depth - 1);
		color = reflect_color(color, new_color, shape->reflection);
	}
	if (shape->refraction)
		color = refraction(dir, shape, rt, depth);
	if (shape->transparency)
	{
		new_color = transperency(dir, rt, depth);
		color = trans_color(color, new_color, shape->transparency);
	}
	return (color);
}
