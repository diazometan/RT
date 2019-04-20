/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 15:26:05 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/04/20 14:59:14 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_vec3	copy_texture(t_texture *texture, t_shape *shape, double uv[2])
{
	int				x;
	int				y;
	double			pixel_block;

	pixel_block = shape->t_dims.z;
	x = (int)((fabs(uv[0])) * M_PI * shape->dims.x * pixel_block);
	y = (int)((uv[1]) * shape->dims.z * pixel_block);
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

t_vec3			cylinder_texture(t_texture *texture, t_shape *shape)
{
	t_vec3	unit;
	t_vec3	r;
	double	u;
	double	v;
	t_matrix		rotation;

	unit = (t_vec3) {0, 1, 0};

	rotation = matrix_multiply(z_rotation_matrix(-shape->unit.z),
							matrix_multiply(y_rotation_matrix(shape->unit.y), x_rotation_matrix(-shape->unit.x)));

	vector_matrix_multiply(rotation, &unit);
	if (fabs(vec3_dot(&unit, &shape->normal)) >= 1.0 - 1e-10)
		return (sphere_texture(texture, shape));
	vec3_subtract(&shape->surface_point, &shape->center, &r);
	vector_matrix_multiply(shape->rotation, &r);

	u = (acos(ft_dclamp(r.x, shape->dims.x * 1.0, shape->dims.x * -1.0) / shape->dims.x) / (2.0 * M_PI));
	if (r.z < 0)
		u = 1.0 - u;
	v = -r.y / shape->dims.z;
	v = (v + 1) / 2;
	move_texture(&u, &v, (double[2]){shape->t_dims.x, shape->t_dims.y});
	if (shape->t_dims.z != 0)
		return (copy_texture(texture, shape, (double[2]){u, v}));
	else
		return (texture_stretching(texture, shape, (double[2]){u, v}));
}
