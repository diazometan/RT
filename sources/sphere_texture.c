/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 15:25:00 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/04/18 16:22:11 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_vec3	copy_texture(t_texture *texture, t_shape *shape, double uv[2])
{
	int				x;
	int				y;

	x = (int)(2 * M_PI * shape->dims.x * PIXELS_BLOCK * fabs(uv[0]));
	y = (int)(M_PI * shape->dims.x * PIXELS_BLOCK * uv[1]);
	return (get_texture_color(texture, (int[2]){x % texture->surface->w, y % texture->surface->h}, uv));
}

static t_vec3	texture_stretching(t_texture *texture, t_shape *shape, double uv[2])
{
	int				x;
	int				y;

	x = (int)(texture->surface->w * fabs(uv[0]));
	y = (int)(texture->surface->h * uv[1]);
	return (get_texture_color(texture, (int[2]){x, y}, uv));
}

t_vec3			sphere_texture(t_texture *texture, t_shape *shape)
{
	t_vec3			normal;
	unsigned char	*pixel;
	double			u;
	double			v;
	int				type;

	vec3_subtract(&shape->surface_point, &shape->center, &normal);
	vector_matrix_multiply(shape->rotation, &normal);
	vec3_normalize(&normal, vec3_length(&normal));
	u = (0.5 + atan2(normal.z, normal.x) / (2 * M_PI));
	v = (0.5 - asin(normal.y) / M_PI);
	move_texture(&u, &v, (double[2]){0.0, 0.05});
	u = ((u * 2.0) - 1.0);

	type = 1;
	if (type == 0)
		return (copy_texture(texture, shape, (double[2]){u, v}));
	else
		return (texture_stretching(texture, shape, (double[2]){u, v}));
}
