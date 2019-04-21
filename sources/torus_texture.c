/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torus_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 15:26:57 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/04/21 15:42:18 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		uv_correct(double *u, double *v, double max_x, double max_y)
{
	(*u) = (*u) * max_x;
	(*v) = (*v) * max_y;
	while(*u >= 1)
		*u = *u - 1.0;
	while(*v >= 1)
		*v = *v - 1.0;
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

	x = (fabs(uv[0])) * (w / 10) * 10;
	y = (uv[1]) * h;
	return (get_texture_color(shape, (int[2]){x, y}, uv, rt));
}

t_vec3			torus_texture(t_texture *texture, t_shape *shape, t_rt *rt)
{
	t_vec3	r;
	double	u;
	double	v;

	vec3_subtract(&rt->source_point, &shape->center, &r);
	vector_matrix_multiply(shape->rotation, &r);
	u = 1.0 - (0.5 + atan2(r.y, r.x) / (2.0 * M_PI));
	v = 1.0 - (0.5 + atan2(r.z, sqrt(r.x * r.x + r.y * r.y) - shape->dims.y) / (2 * M_PI));
	move_texture(&u, &v, (double[2]){shape->t_dims.x, shape->t_dims.y});
	if (shape->t_dims.z != 0)
	{
		if (shape->effect_type == 0)
			uv_correct(&u, &v, (double)texture->surface->w / shape->t_dims.z,
									(double)texture->surface->h / shape->t_dims.z);
		else
			uv_correct(&u, &v, (double)NOISE_WIDTH / shape->t_dims.z,
								(double)NOISE_HEIGHT / shape->t_dims.z);
	}
	else
		uv_correct(&u, &v, 1, 1);
	return (texture_stretching(texture, rt, shape, (double[2]){u, v}));
}
