/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 18:57:11 by lwyl-the          #+#    #+#             */
/*   Updated: 2019/04/16 19:33:28 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_hsv_color			rgb_to_hsv(t_rgb_color rgb)
{
	t_hsv_color		hsv;
	unsigned char	rgb_min;
	unsigned char	rgb_max;

	rgb_min = ft_dmin(rgb.r, ft_dmin(rgb.g, rgb.b));
	rgb_max = ft_dmax(rgb.r, ft_dmax(rgb.g, rgb.b));
	hsv.v = rgb_max;
	if (hsv.v == 0)
	{
		hsv = (t_hsv_color) {0, 0, 0};
		return (hsv);
	}
	hsv.s = 255 * (long)(rgb_max - rgb_min) / hsv.v;
	if (hsv.s == 0)
	{
		hsv.h = 0;
		return (hsv);
	}
	if (rgb_max == rgb.r)
		hsv.h = 0 + 43 * (rgb.g - rgb.b) / (rgb_max - rgb_min);
	else if (rgb_max == rgb.g)
		hsv.h = 85 + 43 * (rgb.b - rgb.r) / (rgb_max - rgb_min);
	else
		hsv.h = 171 + 43 * (rgb.r - rgb.g) / (rgb_max - rgb_min);
	return (hsv);
}

t_rgb_color			hsv_to_rgb(t_hsv_color hsv)
{
	t_rgb_color		rgb;
	unsigned char	region;
	unsigned char	remainder;
	unsigned char	pqt[3];

	if (hsv.s == 0)
		return ((t_rgb_color){hsv.v, hsv.v, hsv.v});
	region = hsv.h / 43;
	remainder = (hsv.h - (region * 43)) * 6;
	pqt[0] = (hsv.v * (255 - hsv.s)) >> 8;
	pqt[1] = (hsv.v * (255 - ((hsv.s * remainder) >> 8))) >> 8;
	pqt[2] = (hsv.v * (255 - ((hsv.s * (255 - remainder)) >> 8))) >> 8;
	if (region == 0)
		rgb = (t_rgb_color){hsv.v, pqt[2], pqt[0]};
	else if (region == 1)
		rgb = (t_rgb_color){pqt[1], hsv.v, pqt[0]};
	else if (region == 2)
		rgb = (t_rgb_color){pqt[0], hsv.v, pqt[2]};
	else if (region == 3)
		rgb = (t_rgb_color){pqt[0], pqt[1], hsv.v};
	else if (region == 4)
		rgb = (t_rgb_color){pqt[2], pqt[0], hsv.v};
	else
		rgb = (t_rgb_color){hsv.v, pqt[0], pqt[1]};
	return (rgb);
}
