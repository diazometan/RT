/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disrubtion_effects.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 17:04:56 by lwyl-the          #+#    #+#             */
/*   Updated: 2019/04/16 17:07:39 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	generateNoise(t_rt *rt)
{
	int	x;
	int	y;

	y = -1;
	while (++y < NOISE_HEIGHT)
	{
		x = -1;
		while (++x < NOISE_WIDTH)
			rt->g_noise[y][x] = (rand() % 32768) / 32768.0;
	}
}

double	smooth_noise(t_rt *rt, double x, double y)
{
	//get fractional part of x and y
	double fractX = x - (int)x;
	double fractY = y - (int)y;

	//wrap around
	int x1 = ((int)x + NOISE_WIDTH) % NOISE_WIDTH;
	int y1 = ((int)y + NOISE_HEIGHT) % NOISE_HEIGHT;

	//neighbor values
	int x2 = (x1 + NOISE_WIDTH - 1) % NOISE_WIDTH;
	int y2 = (y1 + NOISE_HEIGHT - 1) % NOISE_HEIGHT;

	//smooth the noise with bilinear interpolation
	double value = 0.0;
	value += fractX * fractY * rt->g_noise[y1][x1];
	value += (1 - fractX) * fractY * rt->g_noise[y1][x2];
	value += fractX * (1 - fractY) * rt->g_noise[y2][x1];
	value += (1 - fractX) * (1 - fractY) * rt->g_noise[y2][x2];

	return (value);
}

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
	return(128.0 * value / initialSize);
}

int	noise(t_rt *rt, double x, double y)
{
	int	size;

	size = 64;
	return ((int)turbulence(rt, x, y, size) * 0x010101);
}

int			marble(t_rt *rt, int x, int y)
{
	int		color;
	double	xPeriod = 5.0; //defines repetition of marble lines in x direction
	double	yPeriod = 10.0; //defines repetition of marble lines in y direction
	//turbPower = 0 ==> it becomes a normal sine pattern
	double	turbPower = 5.0; //makes twists
	double	turbSize = 32.0; //initial size of the turbulence

	double xyValue = x * xPeriod / NOISE_WIDTH + y * yPeriod / NOISE_HEIGHT +
				turbPower * turbulence(rt, x, y, turbSize) / 256.0;
	double sineValue = 256 * fabs(sin(xyValue * 3.14159));
	color = sineValue;
	return (color * 0x010101);
}
