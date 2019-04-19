/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 15:27:20 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/04/19 19:31:08 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3			box_texture(t_texture *texture, t_shape *shape)
{
	t_vec3	r;
	double	u;
	double	v;
	int x;
	int y;
	unsigned char	*pixel;

	vec3_subtract(&shape->surface_point, &shape->center, &r);
	vector_matrix_multiply(shape->rotation, &r);

	if (fabs(r.x) / shape->dims.x >= 1)
	{
		u = (r.z / shape->dims.z + 1) / 2;
		v = (r.y / shape->dims.y + 1) / 2;
	}
	else if (fabs(r.y) / shape->dims.y >= 1)
	{
		u = (r.x / shape->dims.x + 1) / 2;
		v = (r.z / shape->dims.z + 1) / 2;
	}
	else
	{
		u = (r.x / shape->dims.x + 1) / 2;
		v = (r.y / shape->dims.y + 1) / 2;
	}
	x = (1 - u) * texture->surface->w;
	y = (1 - v) * texture->surface->h;
	pixel = texture->pixel + y * texture->surface->pitch + x * texture->surface->format->BytesPerPixel;
	return ((t_vec3){*(pixel + 2), *(pixel + 1), *pixel});
}
