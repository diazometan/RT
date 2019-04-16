/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_disrubtion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 18:34:27 by lwyl-the          #+#    #+#             */
/*   Updated: 2019/04/16 19:07:58 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			set_color_invers_hsv(t_shape *shape, int rgb_m[3], double light)
{
	int			max_rgb;
	int			min_rgb;
	t_hsv_color	hsv;
	t_rgb_color	rgb;

	rgb_m[0] = shape->color.x * light;
	rgb_m[1] = shape->color.y * light;
	rgb_m[2] = shape->color.z * light;
	rgb = (t_rgb_color){rgb_m[0], rgb_m[1], rgb_m[2]};
	hsv = rgb_to_hsv(rgb);
	hsv.h = 360 - hsv.h;
	rgb = hsv_to_rgb(hsv);
	rgb_m[0] = rgb.r;
	rgb_m[1] = rgb.g;
	rgb_m[2] = rgb.b;
}

void			set_color_grey(t_shape *shape, int rgb_m[3], double light)
{
	int			color;

	rgb_m[0] = shape->color.x;
	rgb_m[1] = shape->color.y;
	rgb_m[2] = shape->color.z;
	color = (rgb_m[0] + rgb_m[1] + rgb_m[2]) / 3;
	rgb_m[0] = (color) * light;
	rgb_m[1] = (color) * light;
	rgb_m[2] = (color) * light;
}

void			set_color_invers(t_shape *shape, int rgb_m[3], double light)
{
	rgb_m[0] = 0xFF - (shape->color.x) * light;
	rgb_m[1] = 0xFF - (shape->color.y) * light;
	rgb_m[2] = 0xFF - (shape->color.z) * light;
}

void			set_color_toon_shading(t_shape *shape, int rgb_m[3],
										double light)
{
	if (light < 0.3)
		light = 0.3;
	else if (light < 0.7)
		light = 0.7;
	else
		light = 1.0;
	rgb_m[0] = shape->color.x * light;
	rgb_m[1] = shape->color.y * light;
	rgb_m[2] = shape->color.z * light;
}
