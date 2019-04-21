/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 15:25:00 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/04/21 19:14:47 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_vec3	copy_texture(t_texture *texture, t_shape *shape, double uv[2], t_rt *rt)
{
	int				x;
	int				y;
	double			pixel_block;
	int				w;
	int				h;

	if (shape->effect_type == 0)
	{
		w = texture->surface->w;
		h = texture->surface->h;
	}
	else
	{
		w = NOISE_WIDTH;
		h = NOISE_HEIGHT;
	}
	pixel_block = shape->t_dims.z;
	x = (int)(0.5 * M_PI * shape->dims.x * pixel_block * fabs(uv[0]));
	y = (int)(2.0 * M_PI * shape->dims.x * pixel_block * uv[1] / 4.0);
	return (get_texture_color(shape, (int[2]){x % w, y % h}, uv, rt));
}

static t_vec3	texture_stretching(t_texture *texture, t_rt *rt, t_shape *shape, double uv[2])
{
	int				x;
	int				y;
	int				w;
	int				h;

	if (shape->effect_type == 0)
	{
		w = texture->surface->w;
		h = texture->surface->h;
	}
	else
	{
		w = NOISE_WIDTH;
		h = NOISE_HEIGHT;
	}

	x = (int)(w * fabs(uv[0]));
	y = (int)(h * uv[1]);
	return (get_texture_color(shape, (int[2]){x, y}, uv, rt));
}

t_vec3			sphere_texture(t_texture *texture, t_shape *shape, t_rt *rt)
{
	t_vec3			normal;
	double			u;
	double			v;

	vec3_subtract(&rt->source_point, &shape->center, &normal);
	vector_matrix_multiply(shape->rotation, &normal);
	vec3_normalize(&normal, vec3_length(&normal));
	u = -(0.5 + atan2(normal.z, normal.x) / (2.0 * M_PI));
	v = (0.5 - asin(normal.y) / M_PI);
	move_texture(&u, &v, (double[2]){shape->t_dims.x, shape->t_dims.y});
	if (shape->t_dims.z != 0)
		return (copy_texture(texture, shape, (double[2]){u, v / 2.0}, rt));
	else
		return (texture_stretching(texture, rt, shape, (double[2]){u, v}));
}
