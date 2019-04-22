/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 10:40:08 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/22 16:55:54 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3		get_texture_color(t_shape *shape, int xy[2], double uv[2], t_rt *rt)
{
	unsigned char	*pixel;
	int				type;

	type = shape->effect_type;
	if (type == 0)
	{
		pixel = shape->texture->pixel + xy[1] * shape->texture->surface->pitch +
				xy[0] * shape->texture->surface->format->BytesPerPixel;
		return ((t_vec3){*(pixel + 2), *(pixel + 1), *pixel});
	}
	else if (type == NOISE)
		return (noise(rt, xy[0], xy[1]));
	else if (type == MARBLE)
		return (marble(rt, xy[0], xy[1]));
	else if (type == CHESS_BOARD)
		return (chess_board(xy[0] + (uv[0] < 0) * 10, xy[1]));
	else if (type == WOOD)
		return (wood(rt, xy[0], xy[1]));
	else
		return ((t_vec3){0, 0, 0});
}

void		move_texture(double *u, double *v, double delta_uv[2])
{
	*u = *u + delta_uv[0];
	*v = *v + delta_uv[1];
	while (*u > 1.0)
		*u = *u - 1.0;
	while (*v > 1.0)
		*v = *v - 1.0;
}
