/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_sup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 19:05:30 by jfrankly          #+#    #+#             */
/*   Updated: 2019/04/18 19:05:31 by jfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static	void	button_event_qlt(t_rtui_min *win_amb, t_rt *rt, t_sdl *sdl)
{
	if (kiss_button_event(&win_amb->button, &win_amb->e, &win_amb->draw))
	{
		/*png adding function*/
		win_amb->quit = 1;
	}
}

static	void	ui_win_lt_init(t_rtui_min *win_amb)
{
	win_amb->quit = 0;
	win_amb->draw = 1;
	kiss_array_new(&win_amb->objects);
	win_amb->renderer = kiss_init("saving file", &win_amb->objects, 300, 200);
	if (!win_amb->renderer)
		return ;
	kiss_window_new(&win_amb->window, NULL, 0, 0, 0, kiss_screen_width,
					kiss_screen_height);
	kiss_label_new(&win_amb->label_intens, &win_amb->window, \
					"enter name of file", 8, 30);
	kiss_entry_new(&win_amb->en_intens, &win_amb->window, 1, "", 10, 65, 280);
	kiss_button_new(&win_amb->button, &win_amb->window, "OK",
					win_amb->window.rect.w / 2 - kiss_normal.w / 2, 150);
	win_amb->window.visible = 1;
}

static	void	kiss_light_draw(t_rtui_min *win_amb)
{
	SDL_RenderClear(win_amb->renderer);
	kiss_window_draw(&win_amb->window, win_amb->renderer);
	kiss_label_draw(&win_amb->label_intens, win_amb->renderer);
	kiss_button_draw(&win_amb->button, win_amb->renderer);
	kiss_entry_draw(&win_amb->en_intens, win_amb->renderer);
	kiss_button_draw(&win_amb->button, win_amb->renderer);
	SDL_RenderPresent(win_amb->renderer);
	win_amb->draw = 0;
}

int				kiss_saving(t_rt *rt, t_sdl *sdl)
{
	t_rtui_min win_amb;

	ui_win_lt_init(&win_amb);
	while (!win_amb.quit)
	{
		SDL_Delay(10);
		while (SDL_PollEvent(&win_amb.e))
		{
			if (win_amb.e.type == SDL_QUIT)
				win_amb.quit = 1;
			kiss_window_event(&win_amb.window, &win_amb.e, &win_amb.draw);
			kiss_entry_event(&win_amb.en_intens, &win_amb.e, &win_amb.draw);
			button_event_qlt(&win_amb, rt, sdl);
		}
		if (!win_amb.draw)
			continue ;
		kiss_light_draw(&win_amb);
	}
	kiss_clean(&win_amb.objects);
	return (0);
}
