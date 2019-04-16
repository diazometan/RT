/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marble.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 18:04:32 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/04/16 14:18:40 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
