/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   progress_bar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 16:23:13 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/21 18:26:39 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	draw_vertical_line(int y_s, int y_e, int x, t_sdl *sdl)
{
	while (++y_s < y_e)
		sdl->pro_data[x + y_s * 600] = 0xFF0000;
}

static void	draw_horizontal_line(int x_s, int x_e, int y, t_sdl *sdl)
{
	while (++x_s < x_e)
		sdl->pro_data[x_s + y * 600] = 0xFF0000;
}

void		draw_borders(t_rt *rt, t_sdl *sdl)
{
	int	xy[4];

	xy[0] = rt->win_width / 5 * 1.95;
	xy[1] = rt->win_width / 5 * 3.06;
	xy[2] = rt->win_height / 2 - 5;
	xy[3] = xy[2] + rt->win_height * 0.083;
	ft_bzero(sdl->surf->pixels, rt->win_width * rt->win_height * 4);
	draw_vertical_line(xy[2], xy[3], xy[0], sdl);
	draw_vertical_line(xy[2], xy[3], xy[1], sdl);
	draw_horizontal_line(xy[0], xy[1], xy[2], sdl);
	draw_horizontal_line(xy[0], xy[1], xy[3], sdl);
	SDL_UpdateWindowSurface(sdl->win);
}

void		progress_bar(double progress, t_rt *rt, t_sdl *sdl)
{
	int	x_s;
	int	x_e;
	int	y_s;
	int	y_e;

	y_e = rt->y_e_bar;
	x_s = rt->x_s_bar;
	x_e = rt->x_s_bar + rt->x_length_bar * progress;
	while (++x_s < x_e)
	{
		y_s = rt->y_s_bar;
		while (++y_s < y_e)
			sdl->pro_data[x_s + y_s * 600] = 0x00AA00;
		SDL_UpdateWindowSurface(sdl->win);
	}
}
