/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   progress_bar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 16:23:13 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/22 17:34:19 by lwyl-the         ###   ########.fr       */
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
	// ft_bzero(sdl->surf->pixels, rt->win_width * rt->win_height * 4);
	draw_vertical_line(xy[2], xy[3], xy[0], sdl);
	draw_vertical_line(xy[2], xy[3], xy[1], sdl);
	draw_horizontal_line(xy[0], xy[1], xy[2], sdl);
	draw_horizontal_line(xy[0], xy[1], xy[3], sdl);
	SDL_UpdateWindowSurface(sdl->win);
}

void		ft_draw_fun(t_rt *rt, t_sdl *sdl, double progress)
{
	t_texture		fun;
	int				color;
	int				x;
	int				y;
	unsigned char	*pixel;

	if ((fun.surface = SDL_LoadBMP("textures/surprise.bmp")) == NULL)
		return;
	fun.pixel = (unsigned char *)fun.surface->pixels;
	x = -1;
	while (++x < (fun.surface->w))
	{
		y = -1;
		while (++y < fun.surface->h)
		{
			pixel = fun.pixel + y * fun.surface->pitch +
					x * fun.surface->format->BytesPerPixel;
			color = ((*(pixel + 2)) << 16) | ((*(pixel + 1)) << 8) | (*pixel);
			sdl->pro_data[((fun.surface->w - x - 1)) + (int)((rt->win_width - (fun.surface->w)) * progress) + (y) * 600 + ((rt->win_height - fun.surface->h)) * 600] = color;
		}
	}
}

void		progress_bar(double progress, t_rt *rt, t_sdl *sdl)
{
	// ft_bzero(sdl->surf->pixels, rt->win_height * rt->win_width * 4);
	ft_draw_fun(rt, sdl, progress);
	SDL_UpdateWindowSurface(sdl->win);
}
