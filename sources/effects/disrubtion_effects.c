/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disrubtion_effects.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 17:04:56 by lwyl-the          #+#    #+#             */
/*   Updated: 2019/04/22 15:42:42 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double		turbulence(t_rt *rt, double x, double y, double size)
{
	double	value;
	double	initial_size;

	value = 0.0;
	initial_size = size;
	while (size >= 1)
	{
		value += smooth_noise(rt, x / size, y / size) * size;
		size /= 2.0;
	}
	return (128.0 * value / initial_size);
}

t_vec3		chess_board(t_rt *rt, int x, int y)
{
	if ((((y / 10) % 2) == ((x / 10) % 2)))
		return ((t_vec3) {rt->color.x, rt->color.y, rt->color.z});
	return ((t_vec3) {0.0, 0.0, 0.0});
}

t_vec3		marble(t_rt *rt, int x, int y)
{
	int		color;
	double	xy_value;
	double	sine_value;

	xy_value = x * 5.0 / NOISE_WIDTH + y * 10.0 / NOISE_HEIGHT +
				5.0 * turbulence(rt, x, y, 32.0) / 256.0;
	sine_value = 256 * fabs(sin(xy_value * 3.14159));
	color = sine_value;
	color = color * 0x010101;
	return ((t_vec3) {(color >> 16) & 0xFF,
			(color >> 8) & 0xFF, (color) & 0xFF});
}

t_vec3		wood(t_rt *rt, int x, int y)
{
	int		color;
	double	x_value;
	double	y_value;
	double	dist_value;
	double	sine_value;

	x_value = (x - NOISE_WIDTH / 2) / (double)(NOISE_WIDTH);
	y_value = (y - NOISE_HEIGHT / 2) / (double)(NOISE_HEIGHT);
	dist_value = sqrt(x_value * x_value + y_value * y_value) +
				0.1 * turbulence(rt, x, y, 32.0) / 256.0;
	sine_value = 128.0 * fabs(sin(2 * 12.0 * dist_value * 3.14159));
	color = (int)(80 + sine_value) * 0x010000;
	color = color + (int)(30 + sine_value) * 0x000100;
	color = color + 30;
	return ((t_vec3) {(color >> 16) & 0xFF,
			(color >> 8) & 0xFF, (color) & 0xFF});
}
