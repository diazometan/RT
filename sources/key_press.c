/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 11:47:19 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/12 20:44:35 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			close_win(t_rt *rt)
{
	free_args(rt->head_shapes, rt->head_light);
	exit(0);
	return (0);
}

static void	move(int key, t_rt *rt)
{
	if (key == KEYBOARD_W)
		rt->camera.z += 0.5;
	if (key == KEYBOARD_S)
		rt->camera.z -= 0.5;
	if (key == KEYBOARD_D)
		rt->camera.x += 0.5;
	if (key == KEYBOARD_A)
		rt->camera.x -= 0.5;
	if (key == SPACE)
		rt->camera.y += 0.5;
	if (key == KEYBOARD_CTRL)
		rt->camera.y -= 0.5;
	if (key == KEYBOARD_R)
	{
		rt->alpha = 0;
		rt->beta = 0;
		rt->camera = (t_coord) {0.0, 0.0, 0.0};
		rt->canvas = (t_coord) {0.0, 0.0, 1.0};
	}
	ft_bzero((void *)rt->mlx.img.img_data, WIN_HEIGHT * WIN_WIDTH * 4);
	create_img(rt);
}

static void	angle_rotation(int key, t_rt *rt)
{
	if (key == KEYBOARD_LEFT)
		rt->alpha += (M_PI * 5.0 / 180);
	if (key == KEYBOARD_RIGHT)
		rt->alpha -= (M_PI * 5.0 / 180);
	if (key == KEYBOARD_UP)
		rt->beta += (M_PI * 5.0 / 180);
	if (key == KEYBOARD_DOWN)
		rt->beta -= (M_PI * 5.0 / 180);
	ft_bzero((void *)rt->mlx.img.img_data, WIN_HEIGHT * WIN_WIDTH * 4);
	create_img(rt);
}

int			key_press(int key, t_rt *rt)
{
	if (key == KEYBOARD_LEFT || key == KEYBOARD_RIGHT ||
		key == KEYBOARD_DOWN || key == KEYBOARD_UP)
		angle_rotation(key, rt);
	if (key == KEYBOARD_W || key == KEYBOARD_S ||
		key == KEYBOARD_A || key == KEYBOARD_D || key == SPACE ||
		key == KEYBOARD_CTRL || key == KEYBOARD_R)
		move(key, rt);
	if (key == ESC)
	{
		free_args(rt->head_shapes, rt->head_light);
		exit(0);
	}
	return (0);
}
