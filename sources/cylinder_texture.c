/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 15:26:05 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/04/18 15:26:13 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3			cylinder_texture(t_texture *texture, t_shape *shape)
{
	t_vec3	unit;
	t_vec3	r;
	double	u;
	double	v;
	//double tmp;
	int x;
	int y;
	unsigned char	*pixel;
	t_matrix		rotation;

	unit = (t_vec3) {0, 1, 0};

	rotation = matrix_multiply(z_rotation_matrix(-shape->unit.z),
							matrix_multiply(y_rotation_matrix(shape->unit.y), x_rotation_matrix(-shape->unit.x)));

	vector_matrix_multiply(rotation, &unit);
	if (fabs(vec3_dot(&unit, &shape->normal)) >= 1.0 - 1e-10)
		return (sphere_texture(texture, shape));
	vec3_subtract(&shape->surface_point, &shape->center, &r);
	vector_matrix_multiply(shape->rotation, &r);

	u = acos(ft_dclamp(r.x, shape->dims.x * 1.0, shape->dims.x * -1.0) / shape->dims.x);
	v = r.y / shape->dims.y;
	u = (u / M_PI) * 2.0 - 1.0;
	v = (v + 1) / 2;
	x = (int)((1 - fabs(u)) * M_PI * shape->dims.x * PIXELS_BLOCK);
	y = (int)((1 - v) * 2.0 * shape->dims.y * PIXELS_BLOCK);
	pixel = texture->pixel + (y % texture->surface->h) * texture->surface->pitch + (x % texture->surface->w) * texture->surface->format->BytesPerPixel;
	// return (wood(x, y));
	// return (marble(x, y));
	// return (noise(x, y));
	//return (chess_board(x, y));
	return ((t_vec3){*(pixel + 2), *(pixel + 1), *pixel});
}
