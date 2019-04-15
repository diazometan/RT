/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 10:40:08 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/15 15:30:34 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3			sphere_texture(t_texture *texture, t_shape *shape)
{
	int				x;
	int				y;
	t_vec3			normal;
	unsigned char	*pixel;

	vec3_subtract(&shape->surface_point, &shape->center, &normal);
	vector_matrix_multiply(shape->rotation, &normal);
	vec3_normalize(&normal, vec3_length(&normal));
	x = (0.5 + atan2(normal.z, normal.x) / (2 * M_PI)) * texture->surface->w;
	y = (0.5 - asin(normal.y) / M_PI) * texture->surface->h;
	pixel = texture->pixel + y * texture->surface->pitch + x * texture->surface->format->BytesPerPixel;
	return ((t_vec3){*(pixel + 2), *(pixel + 1), *pixel});
}

t_vec3			plane_texture(t_texture *texture, t_shape *shape)
{
	int				x;
	int				y;
	double			u;
	double			v;
	unsigned char	*pixel;

	u = shape->surface_point.z;
	v = shape->surface_point.y;
	if (fabs(shape->unit.z) >= fabs(shape->unit.y) && fabs(shape->unit.z) >= fabs(shape->unit.x))
	{
		u = shape->surface_point.x;
		v = shape->surface_point.y;
	}
	else if (fabs(shape->unit.y) >= fabs(shape->unit.x) && fabs(shape->unit.y) >= fabs(shape->unit.z))
	{
		u = shape->surface_point.x;
		v = shape->surface_point.z;
	}
	while (u > 2)
		u -= 2;
	while (u < 0)
		u += 2;
	while (v > 2)
		v -= 2;
	while (v < 0)
		v += 2;
	x = u * texture->surface->w / 2;
	y = (2 - v) * texture->surface->h / 2;
	pixel = texture->pixel + y * texture->surface->pitch + x * texture->surface->format->BytesPerPixel;
	return ((t_vec3){*(pixel + 2), *(pixel + 1), *pixel});
}

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
	u = u / M_PI;
	v = (v + 1) / 2;
	x = (1 - u) * texture->surface->w;
	y = (1 - v) * texture->surface->h;
	pixel = texture->pixel + y * texture->surface->pitch + x * texture->surface->format->BytesPerPixel;
	return ((t_vec3){*(pixel + 2), *(pixel + 1), *pixel});
}

t_vec3			cone_texture(t_texture *texture, t_shape *shape)
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

	//u = acos(ft_dclamp(r.x , shape->dims.x * 1.0, shape->dims.x * -1.0) / (shape->dims.x * (1 - r.y / shape->dims.y)));
	// v = r.y / shape->dims.y;
	// //u = u / M_PI;
	// v = (v + 1) / 2;
	// u = acos(ft_dclamp(ft_dclamp(r.x , shape->dims.x * 1.0, shape->dims.x * -1.0) / (shape->dims.x * (shape->dims.y - v)), 1.0, -1.0));
	// u = u / M_PI;
	v = r.y / shape->dims.y;
	u = acos(ft_dclamp(r.x / (shape->dims.x + (0.0 - shape->dims.x) * v), 1.0, -1.0)) / M_PI;
	v = (v + 1) / 2;
	//printf("%f   %f\n", u, v);
	if (r.z < 0)
		u = 1 - u;
	x = (1 - u) * texture->surface->w;
	y = (1 - v) * texture->surface->h;
	pixel = texture->pixel + y * texture->surface->pitch + x * texture->surface->format->BytesPerPixel;
	return ((t_vec3){*(pixel + 2), *(pixel + 1), *pixel});
}

t_vec3			torus_texture(t_texture *texture, t_shape *shape)
{
	t_vec3	r;
	double	u;
	double	v;
	int x;
	int y;
	unsigned char	*pixel;

	vec3_subtract(&shape->surface_point, &shape->center, &r);
	vector_matrix_multiply(shape->rotation, &r);
	//vec3_normalize(&r, vec3_length(&r));

	/*v = 0.5 - asin(r.z / shape->dims.x) / M_PI;
	u = (acos(r.x / (shape->dims.x + shape->dims.y * cos(2 * M_PI * v)))) / M_PI;
	//printf("%f   %f\n", v, u);
	x = (1 - u) * texture->surface->w;
	y = (1 - v) * texture->surface->h;*/
	u = 0.5 + atan2(r.y, r.x) / (2 * M_PI);
	v = 0.5 + atan2(r.z, sqrt(r.x * r.x + r.y * r.y) - shape->dims.y) / (2 * M_PI);
	x = (1 - u) * texture->surface->w;
	y = (1 - v) * texture->surface->h;
	pixel = texture->pixel + y * texture->surface->pitch + x * texture->surface->format->BytesPerPixel;
	return ((t_vec3){*(pixel + 2), *(pixel + 1), *pixel});
}

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
