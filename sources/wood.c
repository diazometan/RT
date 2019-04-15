/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wood.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 18:03:56 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/04/12 18:04:06 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			wood(int x, int y)
{
	int color;

	double xyPeriod = 12.0; //number of rings
	double turbPower = 0.1; //makes twists
	double turbSize = 32.0; //initial size of the turbulence

	double xValue = (x - NOISE_WIDTH / 2) / (double)(NOISE_WIDTH);
	double yValue = (y - NOISE_HEIGHT / 2) / (double)(NOISE_HEIGHT);
	double distValue = sqrt(xValue * xValue + yValue * yValue) + turbPower * turbulence(x, y, turbSize) / 256.0;
	double sineValue = 128.0 * fabs(sin(2 * xyPeriod * distValue * 3.14159));
	color = (int)(80 + sineValue) * 0x010000;
	color = color + (int)(30 + sineValue) * 0x000100;
	color = color + 30;
	return (color);
}
