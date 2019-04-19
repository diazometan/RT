/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 15:27:20 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/04/19 19:52:09 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		uv_correct(double *u, double *v, double max_x, double max_y)
{
	(*u) = (*u) / max_x;
	(*v) = (*v) / max_y;
	while(*u >= 1)
		*u = *u - 1.0;
	while(*v >= 1)
		*v = *v - 1.0;
}

static t_vec3	texture_stretching(t_texture *texture, t_shape *shape, double uv[2])
{
	int				x;
	int				y;

	x = (1 - uv[0]) * texture->surface->w;
	y = (1 - uv[1]) * texture->surface->h;
	return (get_texture_color(texture, (int[2]){x, y}, uv));
}

t_vec3			box_texture(t_texture *texture, t_shape *shape)
{
	t_vec3	r;
	double	u;
	double	v;

	vec3_subtract(&shape->surface_point, &shape->center, &r);
	vector_matrix_multiply(shape->rotation, &r);

	if (r.x / shape->dims.x >= 1)
	{
		u = 1.0 - (r.z / shape->dims.z + 1) / 2;
		v = (r.y / shape->dims.y + 1) / 2;
	}
	else if (r.x / shape->dims.x <= -1)
	{
		u = (r.z / shape->dims.z + 1) / 2;
		v = (r.y / shape->dims.y + 1) / 2;
	}
	else if ((r.y) / shape->dims.y >= 1)
	{
		u = 1 - (r.x / shape->dims.x + 1) / 2;
		v = (r.z / shape->dims.z + 1) / 2;
	}
	else if ((r.y) / shape->dims.y <= -1)
	{
		u = (r.x / shape->dims.x + 1) / 2;
		v = (r.z / shape->dims.z + 1) / 2;
	}
	else if (r.z / shape->dims.z >= 1)
	{
		u = (r.x / shape->dims.x + 1) / 2;
		v = (r.y / shape->dims.y + 1) / 2;
	}
	else
	{
		u = 1.0 - (r.x / shape->dims.x + 1) / 2;
		v = (r.y / shape->dims.y + 1) / 2;
	}
	move_texture(&u, &v, (double[2]){shape->t_dims.x, shape->t_dims.y});
	if (shape->t_dims.z != 0)
		uv_correct(&u, &v, (double)texture->surface->w / shape->t_dims.z,
							(double)texture->surface->h / shape->t_dims.z);
	else
		uv_correct(&u, &v, 1, 1);
	return (texture_stretching(texture, shape, (double[2]){u, v}));
}
