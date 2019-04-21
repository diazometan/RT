/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:29:21 by lwyl-the          #+#    #+#             */
/*   Updated: 2019/04/21 14:33:55 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	check_color(int rgb[3])
{
	int		i;
	int		j;
	int		f;
	int		tmp;
	int		index;

	if (rgb[0] > 255 || rgb[1] > 255 || rgb[2] > 255)
		return (0xffffff);
	// f = 1;
	// while (f)
	// {
	// 	i = -1;
	// 	f = 0;
	// 	while (++i < 3)
	// 		if (rgb[i] > 255)
	// 		{
	// 			f = 1;
	// 			tmp = rgb[i] - 255;
	// 			rgb[i] = 255;
	// 			j = -1;
	// 			while (++j < 3)
	// 			{
	// 				index++;
	// 				if (j != i)
	// 					rgb[j] += tmp / 2;
	// 			}
	// 			break ;
	// 		}
	// }
	if (index > 0)
		printf("%d\n", index);
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
	get_intersection_point(&rt->source_point, dir,
							rt->t_closest, &rt->source_point);
	get_normal(&rt->source_point, &rt->normal, shape);
	if (shape->texture != NULL)
	{
		rt->color = shape->map_texture(shape->texture, shape, rt);
		shape->color = rt->color;
	}
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
	choose_color(rt, shape, rgb, light);
	color = check_color(rgb);
	if (depth > 0 && shape->reflection)
	{
		new_color = reflection(dir, shape, rt, depth - 1);
		color = reflect_color(color, new_color, shape->reflection);
	}
	if (shape->refraction)
		color = refraction(dir, shape, rt, depth);
	if (shape->transparency)
	{
		new_color = transperency(dir, shape, rt, depth);
		color = trans_color(color, new_color, shape->transparency);
	}
	return (color);
}
