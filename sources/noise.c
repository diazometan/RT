/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 17:00:40 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/04/17 16:03:53 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	generate_noise(t_rt *rt)
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

t_vec3	noise(t_rt *rt, double x, double y)
{
	int	size;
	int	color;

	size = 64;
	color = ((int)turbulence(rt, x, y, size) * 0x010101);
	return ((t_vec3) {(color >> 16) & 0xFF,
			(color >> 8) & 0xFF, (color) & 0xFF});
}

double	smooth_noise(t_rt *rt, double x, double y)
{
	double fractX;
	double fractY;
	int xy[4];
	double value;

	fractX = x - (int)x;
	fractY = y - (int)y;
	xy[0] = ((int)x + NOISE_WIDTH) % NOISE_WIDTH;
	xy[1] = ((int)y + NOISE_HEIGHT) % NOISE_HEIGHT;
	xy[2] = (xy[0] + NOISE_WIDTH - 1) % NOISE_WIDTH;
	xy[3] = (xy[1] + NOISE_HEIGHT - 1) % NOISE_HEIGHT;
	value = 0.0;
	value += fractX * fractY * rt->g_noise[xy[1]][xy[0]];
	value += (1 - fractX) * fractY * rt->g_noise[xy[1]][xy[2]];
	value += fractX * (1 - fractY) * rt->g_noise[xy[3]][xy[0]];
	value += (1 - fractX) * (1 - fractY) * rt->g_noise[xy[3]][xy[2]];

	return (value);
}
