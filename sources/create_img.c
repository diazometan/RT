/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 11:29:08 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/15 12:27:19 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	init_camera_ray(int x, int y, t_shape *shape, t_rt *rt)
{
	t_matrix	rotation;

	rotation = matrix_multiply(x_rotation_matrix(rt->angle.x),
								y_rotation_matrix(rt->angle.y));
	shape->ray.x = (double)((-rt->win_width / 2) + x) /
					rt->win_width + rt->camera.x / rt->win_width;
	shape->ray.y = (double)(rt->win_height / 2 - y) /
					rt->win_height + rt->camera.y / rt->win_height;
	shape->ray.z = 1.0;
	normalize_vector(&(shape->ray), vector_length(&shape->ray));
	vector_matrix_multiply(rotation, shape);
}

void		get_pixel(int x, int y, t_rt *rt, t_sdl *sdl)
{
	t_shape	*closest;
	t_shape *shape;

	shape = rt->head_shapes;
	closest = NULL;
	rt->t_closest = INT_MAX;
	while (shape != NULL)
	{
		init_camera_ray(x, y, shape, rt);
		if (check_intersection(shape, rt))
			closest = shape;
		shape = shape->next;
	}
	if (closest != NULL)
		sdl->img_data[x + y * rt->win_width] = get_color(closest, rt);
	else
		sdl->img_data[x + y * rt->win_width] = 0x0;
}

void		create_img(t_rt *rt, t_sdl *sdl)
{
	int		x;
	int		y;
	int		x_limit;
	int		y_limit;

	y = -1;
	x_limit = rt->win_width;
	y_limit = rt->win_height;
	while (++y < y_limit)
	{
		x = -1;
		while (++x < x_limit)
			get_pixel(x, y, rt, sdl);
	}
	SDL_UpdateWindowSurface(sdl->win);
}
