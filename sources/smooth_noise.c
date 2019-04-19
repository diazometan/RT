/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smooth_noise.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 16:29:45 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/04/12 17:03:00 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "rt.h"

double	smooth_noise(double x, double y)
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
   value += fractX     * fractY     * g_noise[y1][x1];
   value += (1 - fractX) * fractY     * g_noise[y1][x2];
   value += fractX     * (1 - fractY) * g_noise[y2][x1];
   value += (1 - fractX) * (1 - fractY) * g_noise[y2][x2];

   return value;
}