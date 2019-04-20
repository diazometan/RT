/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   progress_bar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 16:23:13 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/20 20:53:05 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	draw_line(int x_s, int x_e, int y_s, int y_e, t_sdl *sdl)
{
	if (x_s == x_e)
	{
		while (++y_s < y_e)
			sdl->pro_data[x_s + y_s * 600] = 0xFF0000;
	}
	else if (y_s == y_e)
	{
		while (++x_s < x_e)
			sdl->pro_data[x_s + y_s * 600] = 0xFF0000;
	}
}

void	progress_bar(double progress, t_rt *rt, t_sdl *sdl)
{
	static int	flag = 1;
	int	x;
	int	x_s;
	int	x_e;
	int	y;
	int	y_limit;
	//int	*img_data;
	
	//img_data = sdl->img_data;
	if (flag)
	{
		y = rt->win_height / 2 - 5;
		x_s = rt->win_width / 5 * 2 - 5;
		x_e = rt->win_width / 5 * 3 + 5;
		y_limit = y + 50;
		draw_line(x_s, x_s, y, y_limit, sdl);
		draw_line(x_e, x_e, y, y_limit, sdl);
		draw_line(x_s, x_e, y, y, sdl);
		draw_line(x_s, x_e, y_limit, y_limit, sdl);
		flag = 0;
	}
	y = rt->win_height / 2;
	x_s = rt->win_width / 5 * 2;
	x_e = rt->win_width / 5 * 3;
	x_e = x_s + (x_e - x_s) * progress;
	//printf("progress - %f\n", progress);
	//printf("x_s - %d\n", x_s);
	//printf("x_e - %d\n\n\n", x_e);
	y_limit = y + 40;
	while (++y < y_limit)
	{
		//x = width / 2;
		x = x_s;
		while (++x < x_e)
			sdl->pro_data[x + y * 600] = 0x00AA00;
	}
	SDL_UpdateWindowSurface(sdl->win);
}
