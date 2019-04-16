/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turbulence.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 16:31:57 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/04/15 19:41:25 by lwyl-the         ###   ########.fr       */
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
	return(128.0 * value / initialSize);
}
