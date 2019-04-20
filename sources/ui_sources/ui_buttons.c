/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_files.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 19:05:19 by jfrankly          #+#    #+#             */
/*   Updated: 2019/04/18 19:05:19 by jfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	button_event_hide(t_rtui *ui)
{
	if (kiss_button_event(&ui->button_hide, &ui->e, &ui->draw))
	{
		ui->quit = 1;
	}
}

static void	button_event_exit(t_rtui *ui, t_rt *rt, t_sdl *sdl)
{
	if (kiss_button_event(&ui->button_ex, &ui->e, &ui->draw))
	{
		ui->quit = 1;
		if (rt->win_width)
			free_args(rt->head_shapes, rt->head_light, rt->head_textures);
		SDL_DestroyWindow(sdl->win);
		SDL_Quit();
		exit(1);
	}
}

static void	button_light_event(t_rtui *ui, t_rt *rt, t_sdl *sdl)
{
	if (kiss_button_event(&ui->button_light, &ui->e, &ui->draw))
	{
		kiss_light(rt, sdl);
	}
}

static void	button_ok1_event(t_rtui *ui, t_rt *rt, t_sdl *sdl)
{
	if (kiss_button_event(&ui->button_ok1, &ui->e, &ui->draw))
	{
		if (!(ft_strstr(ui->label_sel.text, ".json")))
		{
			kiss_error("should be \".json\"");
			return ;
		}
		if (rt->win_width)
			free_args(rt->head_shapes, rt->head_light, rt->head_textures);
/* 		SDL_FreeSurface(sdl->surf); //DOESNT WORK??? NO LEAKS??? WTF
		sdl->surf = SDL_GetWindowSurface(sdl->win);
		sdl->img_data = (int *)sdl->surf->pixels; */
		init_rt(rt, ui->file_path);
		create_img(rt, sdl);
	}
}

void		button_events_main(t_rtui *ui, t_rt *rt, t_sdl *sdl)
{
	button_event_hide(ui);
	button_event_exit(ui, rt, sdl);
	button_ok1_event(ui, rt, sdl);
	button_light_event(ui, rt, sdl);
}
