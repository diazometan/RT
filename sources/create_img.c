/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 11:29:08 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/12 20:44:21 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	init_camera_ray(int x, int y, t_shape *shape, t_rt *rt)
{
	t_matrix	rotation;

	rotation = matrix_multiply(x_rotation_matrix(rt->angle.x),
								y_rotation_matrix(rt->angle.y));
	shape->ray.x = (double)((-WIN_WIDTH_HALF) + x) /
					WIN_WIDTH + rt->camera.x / WIN_WIDTH;
	shape->ray.y = (double)(WIN_HEIGHT_HALF - y) /
					WIN_HEIGHT + rt->camera.y / WIN_WIDTH;
	shape->ray.z = 1.0;
	normalize_vector(&(shape->ray), vector_length(&shape->ray));
	vector_matrix_multiply(rotation, shape);
}

void		get_pixel(int x, int y, t_rt *rt, t_sdl *sdl)
{
	t_shape	*first;
	t_shape *shape;

	shape = rt->head_shapes;
	first = NULL;
	rt->t_closest = INT_MAX;
	while (shape != NULL)
	{
		init_camera_ray(x, y, shape, rt);
		if (check_intersection(shape, rt))
			first = shape;
		shape = shape->next;
	}
	//if (first != NULL)
		//rt->mlx.img.img_data[x + y * WIN_WIDTH] = get_color(first, rt);
	if (first != NULL)
		sdl->img_data[x + y * WIN_WIDTH] = get_color(first, rt);
	else
		sdl->img_data[x + y * WIN_WIDTH] = 0x0;
}

void		create_img(t_rt *rt, t_sdl *sdl)
{
	int		x;
	int		y;

	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
			get_pixel(x, y, rt, sdl);
	}
	SDL_UpdateWindowSurface(sdl->win);
	//mlx_put_image_to_window(rt->mlx.mlx_ptr, rt->mlx.win_ptr,
								//rt->mlx.img.img_ptr, 0, 0);
}
