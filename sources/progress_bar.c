/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   progress_bar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 16:23:13 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/22 19:48:03 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		progress_bar(double progress, t_rt *rt, t_sdl *sdl)
{
	int	x_s;
	int	x_e;
	int	y_s;
	int	y_e;

	x_s = 0;
	x_e = rt->win_width * progress;
	y_e = rt->win_height;
	while (++x_s < x_e)
	{
		y_s = rt->win_height * 0.98;
		while (++y_s < y_e)
		{
			if (progress < 0.3)
				sdl->pro_data[x_s + y_s * rt->win_width] = 0xFF0000;
			else if (progress >= 0.3 && progress < 0.6)
				sdl->pro_data[x_s + y_s * rt->win_width] = 0xFF6600;
			else if (progress >= 0.6 && progress < 0.9)
				sdl->pro_data[x_s + y_s * rt->win_width] = 0xFFC900;
			else
				sdl->pro_data[x_s + y_s * rt->win_width] = 0x00AA00;
		}
	}
	SDL_UpdateWindowSurface(sdl->win);
}
