/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torus_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 15:26:57 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/04/18 15:27:08 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3			torus_texture(t_texture *texture, t_shape *shape)
{
	t_vec3	r;
	double	u;
	double	v;
	int x;
	int y;
	unsigned char	*pixel;

	vec3_subtract(&shape->surface_point, &shape->center, &r);
	vector_matrix_multiply(shape->rotation, &r);
	//vec3_normalize(&r, vec3_length(&r));

	/*v = 0.5 - asin(r.z / shape->dims.x) / M_PI;
	u = (acos(r.x / (shape->dims.x + shape->dims.y * cos(2 * M_PI * v)))) / M_PI;
	//printf("%f   %f\n", v, u);
	x = (1 - u) * texture->surface->w;
	y = (1 - v) * texture->surface->h;*/
	u = 0.5 + atan2(r.y, r.x) / (2 * M_PI);
	u = 1.0 - 2.0 * u;
	v = 0.5 + atan2(r.z, sqrt(r.x * r.x + r.y * r.y) - shape->dims.y) / (2 * M_PI);
	x = (1.0 - fabs(u)) * (texture->surface->w / 10) * 10;
	y = (1.0 - v) * texture->surface->h;
	pixel = texture->pixel + y * texture->surface->pitch + x * texture->surface->format->BytesPerPixel;
	//return (chess_board(x, y));
	return ((t_vec3){*(pixel + 2), *(pixel + 1), *pixel});
}
