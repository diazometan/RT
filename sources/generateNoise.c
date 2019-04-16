/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generateNoise.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 16:27:37 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/04/15 19:38:12 by lwyl-the         ###   ########.fr       */
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
