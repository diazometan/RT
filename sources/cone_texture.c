/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 15:26:29 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/04/19 15:52:52 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3			cone_texture(t_texture *texture, t_shape *shape)
{
	t_vec3	unit;
	t_vec3	r;
	double	u;
	double	v;
	int x;
	int y;
	unsigned char	*pixel;
	t_matrix		rotation;
	t_vec3	unit1;
	t_vec3	angle;

	unit = (t_vec3) {0, 1, 0};
	unit1 = (t_vec3) {1, 0, 0};

	rotation = matrix_multiply(z_rotation_matrix(-shape->unit.z),
							matrix_multiply(y_rotation_matrix(shape->unit.y), x_rotation_matrix(-shape->unit.x)));

	vector_matrix_multiply(rotation, &unit);
	if (fabs(vec3_dot(&unit, &shape->normal)) >= 1.0 - 1e-10)
		return (sphere_texture(texture, shape));
	vec3_subtract(&shape->surface_point, &shape->center, &r);
	vector_matrix_multiply(shape->rotation, &r);

	angle = (t_vec3){r.x, 0, r.z};
	vec3_normalize(&angle, vec3_length(&angle));
	u = acos(vec3_dot(&angle, &unit1)) / M_PI;
	v = r.y / shape->dims.z;
	v = (v + 1) / 2;
	x = (1 - u) * texture->surface->w;
	y = (1 - v) * texture->surface->h;
	pixel = texture->pixel + y * texture->surface->pitch + x * texture->surface->format->BytesPerPixel;
	// return (wood(x, y));
	// return (marble(x, y));
	// return (noise(x, y));
	//return (chess_board(x, y));
	return ((t_vec3){*(pixel + 2), *(pixel + 1), *pixel});
}
