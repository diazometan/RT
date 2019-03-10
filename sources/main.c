/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 10:51:40 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/09 13:36:00 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "RTv1");
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx->img.img_data = (int *)mlx_get_data_addr(mlx->img.img_ptr,
		&mlx->img.bpp, &mlx->img.size_line, &mlx->img.endian);
	ft_bzero((void *)mlx->img.img_data, WIN_HEIGHT * WIN_WIDTH * 4);
}

void	init_rt(t_rt *rt, char *file_shapes,
				char *file_light_sources, char *file_camera)
{
	rt->head_shapes = get_shapes(file_shapes);
	rt->head_light = get_light_sources(file_light_sources, rt);
	init_camera(file_camera, rt);
	rt->canvas = (t_coord) {0.0, 0.0, 1.0};
}

int		main(int args, char **argv)
{
	t_rt	rt;

	if (args != 4)
	{
		ft_putstr("\033[0;31musage: ./RTv1 [file_shapes]\
[file_light_sources] [file_camera]\n");
		return (1);
	}
	init_rt(&rt, argv[1], argv[2], argv[3]);
	init_mlx(&rt.mlx);
	create_img(&rt);
	mlx_hook(rt.mlx.win_ptr, 2, 0, &key_press, &rt);
	mlx_hook(rt.mlx.win_ptr, 17, 0, &close_win, &rt);
	mlx_loop(rt.mlx.mlx_ptr);
	return (0);
}
