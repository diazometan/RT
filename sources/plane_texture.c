/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 15:25:36 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/04/19 17:03:51 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3			plane_texture(t_texture *texture, t_shape *shape)
{
	int				x;
	int				y;
	double			u;
	double			v;
	unsigned char	*pixel;
	t_vec3			r;

	vec3_subtract(&shape->surface_point, &shape->center, &r);
	vector_matrix_multiply(shape->rotation, &r);
	u = r.x;
	v = r.z;
	while (u > 2)
		u -= 2;
	while (u < 0)
		u += 2;
	while (v > 2)
		v -= 2;
	while (v < 0)
		v += 2;
	x = u * texture->surface->w / 2;
	y = (2 - v) * texture->surface->h / 2;
	pixel = texture->pixel + y * texture->surface->pitch + x * texture->surface->format->BytesPerPixel;
	// return (wood(x, y));
	// return (noise(x, y));
	//return (chess_board(x, y));
	return ((t_vec3){*(pixel + 2), *(pixel + 1), *pixel});
}
