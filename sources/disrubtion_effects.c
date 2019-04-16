/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disrubtion_effects.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 17:04:56 by lwyl-the          #+#    #+#             */
/*   Updated: 2019/04/16 20:03:59 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	turbulence(t_rt *rt, double x, double y, double size)
{
	double	value;
	double	initialSize = size;

	value = 0.0;
	while(size >= 1)
	{
		value += smooth_noise(rt, x / size, y / size) * size;
		size /= 2.0;
	}
	return (128.0 * value / initialSize);
}

t_vec3		chess_board(int x, int y)
{
	if ((((y / 10) % 2) == ((x / 10) % 2)))
		return ((t_vec3) {255.0, 255.0, 255.0});
	return ((t_vec3) {0.0, 0.0, 0.0});
}

t_vec3		marble(t_rt *rt, int x, int y)
{
	int		color;
	double	xyValue;
	double	sineValue;

	xyValue = x * 5.0 / NOISE_WIDTH + y * 10.0 / NOISE_HEIGHT +
				5.0 * turbulence(rt, x, y, 32.0) / 256.0;
	sineValue = 256 * fabs(sin(xyValue * 3.14159));
	color = sineValue;
	color = color * 0x010101;
	return ((t_vec3) {(color >> 16) & 0xFF,
			(color >> 8) & 0xFF, (color) & 0xFF});
}

t_vec3		wood(t_rt *rt, int x, int y)
{
	int		color;
	double	xValue;
	double	yValue;
	double	distValue;
	double	sineValue;

	xValue = (x - NOISE_WIDTH / 2) / (double)(NOISE_WIDTH);
	yValue = (y - NOISE_HEIGHT / 2) / (double)(NOISE_HEIGHT);
	distValue = sqrt(xValue * xValue + yValue * yValue) +
				0.1 * turbulence(rt, x, y, 32.0) / 256.0;
	sineValue = 128.0 * fabs(sin(2 * 12.0 * distValue * 3.14159));
	color = (int)(80 + sineValue) * 0x010000;
	color = color + (int)(30 + sineValue) * 0x000100;
	color = color + 30;
	return ((t_vec3) {(color >> 16) & 0xFF,
			(color >> 8) & 0xFF, (color) & 0xFF});
}
