/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generateNoise.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 16:27:37 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/04/12 16:36:40 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	generateNoise()
{
	int	x;
	int	y;

	y = -1;
	while (++y < NOISE_HEIGHT)
	{
		x = -1;
		while (++x < NOISE_WIDTH)
			noise[y][x] = (rand() % 32768) / 32768.0;
	}
}