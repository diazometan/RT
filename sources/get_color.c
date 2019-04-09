/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:29:21 by lwyl-the          #+#    #+#             */
/*   Updated: 2019/04/09 19:20:12 by lwyl-the         ###   ########.fr       */
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

/*static int	refract_color(int color, int refracted_color)
{
	int		rgb_ref[3];
	color = 0;

	rgb_ref[0] = (refracted_color >> 16 & 0xFF);
	rgb_ref[1] = (refracted_color >> 8 & 0xFF);
	rgb_ref[2] = (refracted_color & 0xFF);
	return ((rgb_ref[0] << 16) | (rgb_ref[1] << 8) | rgb_ref[2]);
}*/

/*static int	reflect_color(int color, int reflected_color, double reflection)
{
	int		rgb_ref[3];

	rgb_ref[0] = (color >> 16 & 0xFF) * (1 - reflection) +
					(reflected_color >> 16 & 0xFF) * reflection;
	rgb_ref[1] = (color >> 8 & 0xFF) * (1 - reflection) +
					(reflected_color >> 8 & 0xFF) * reflection;
	rgb_ref[2] = (color & 0xFF) * (1 - reflection) +
					(reflected_color & 0xFF) * reflection;
	return ((rgb_ref[0] << 16) | (rgb_ref[1] << 8) | rgb_ref[2]);
}*/

int		get_color(t_vec3 *dir, t_shape *shape, t_rt *rt, int depth)
{
	int		rgb[3];
	double	light = 0.0;
	double	color;
	//double	new_color;

	get_intersection_point(rt->source_point, dir, rt->t_closest, &shape->surface_point);
	get_normal(shape);
	light = get_light(dir, shape, rt);
	//light = emission(shape, rt, depth);
	if (shape->texture != NULL)
	{
		if (shape->figure == SPHERE)
			shape->color = sphere_texture(shape->texture, shape);
		else if (shape->figure == PLANE)
			shape->color = plane_texture(shape->texture, shape);
		else if (shape->figure == CYLINDER)
			shape->color = cylinder_texture(shape->texture, shape);
		else if (shape->figure == CONE)
			shape->color = cone_texture(shape->texture, shape);
		else if (shape->figure == TORUS)
			shape->color = torus_texture(shape->texture, shape);
	}
	rgb[0] = (shape->color >> 16 & 0xFF) * light;
	rgb[1] = (shape->color >> 8 & 0xFF) * light;
	rgb[2] = (shape->color & 0xFF) * light;
	color = check_color(rgb);
	/*if (shape->emission == 0.0)
		color = emission(shape, rt, depth);
	else
		color = 0xFFFFFF;*/

	//ADDING REFLECTION
	/*if (depth > 0 && shape->reflection)
	{
		new_color = reflection(dir, shape, rt, depth - 1);
		color = reflect_color(color, new_color, shape->reflection);
	}*/
	//END

	return (color);
}
