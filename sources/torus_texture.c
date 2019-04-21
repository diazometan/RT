/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torus_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 15:26:57 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/04/21 13:35:50 by lwyl-the         ###   ########.fr       */
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

static t_vec3	texture_stretching(t_texture *texture, double uv[2])
{
	int				x;
	int				y;

	x = (fabs(uv[0])) * (texture->surface->w / 10) * 10;
	y = (uv[1]) * texture->surface->h;
	return (get_texture_color(texture, (int[2]){x, y}, uv));
}

t_vec3			torus_texture(t_texture *texture, t_shape *shape, t_rt *rt)
{
	t_vec3	r;
	double	u;
	double	v;

	vec3_subtract(&rt->source_point, &shape->center, &r);
	vector_matrix_multiply(shape->rotation, &r);
	//vec3_normalize(&r, vec3_length(&r));

	/*v = 0.5 - asin(r.z / shape->dims.x) / M_PI;
	u = (acos(r.x / (shape->dims.x + shape->dims.y * cos(2 * M_PI * v)))) / M_PI;
	//printf("%f   %f\n", v, u);
	x = (1 - u) * texture->surface->w;
	y = (1 - v) * texture->surface->h;*/
	u = 1.0 - (0.5 + atan2(r.y, r.x) / (2.0 * M_PI));
	v = 1.0 - (0.5 + atan2(r.z, sqrt(r.x * r.x + r.y * r.y) - shape->dims.y) / (2 * M_PI));
	move_texture(&u, &v, (double[2]){shape->t_dims.x, shape->t_dims.y});
	if (shape->t_dims.z != 0)
		uv_correct(&u, &v, (double)texture->surface->w / shape->t_dims.z,
							(double)texture->surface->h / shape->t_dims.z);
	else
		uv_correct(&u, &v, 1, 1);
	return (texture_stretching(texture, (double[2]){u, v}));
}
