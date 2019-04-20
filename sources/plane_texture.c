/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 15:25:36 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/04/20 16:11:28 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		uv_correct(double *u, double *v, double max_x, double max_y)
{
	while ((*u) > max_x)
		(*u) = (*u) - max_x;
	while ((*u) < 0)
		(*u) = (*u) + max_x;
	while ((*v) > max_y)
		(*v) = (*v) - max_y;
	while ((*v) < 0)
		(*v) = (*v) + max_y;
	(*u) = (*u) / max_x;
	(*v) = (*v) / max_y;
}

static t_vec3	texture_stretching(t_texture *texture, t_shape *shape, double uv[2])
{
	int				x;
	int				y;

	x = uv[0] * texture->surface->w;
	y = (1 - uv[1]) * texture->surface->h;
	return (get_texture_color(texture, (int[2]){x, y}, uv));
}

t_vec3			plane_texture(t_texture *texture, t_shape *shape)
{
	double			u;
	double			v;
	t_vec3			r;

	vec3_subtract(&shape->surface_point, &shape->center, &r);
	vector_matrix_multiply(shape->rotation, &r);
	u = r.x / 2.0;
	v = r.z / 2.0;
	move_texture(&u, &v, (double[2]){shape->t_dims.x, shape->t_dims.y});
	if (shape->t_dims.z != 0)
		uv_correct(&u, &v, (double)texture->surface->w / shape->t_dims.z,
							(double)texture->surface->h / shape->t_dims.z);
	else
		uv_correct(&u, &v, 1, 1);
	return (texture_stretching(texture, shape, (double[2]){u, v}));
}
