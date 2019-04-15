/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turbulence.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 16:31:57 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/04/12 16:36:38 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	turbulence(double x, double y, double size)
{
	double	value;
	double	initialSize = size;

	value = 0.0;
	while(size >= 1)
	{
		value += smooth_noise(x / size, y / size) * size;
		size /= 2.0;
	}
	return(128.0 * value / initialSize);
}