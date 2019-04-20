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

static	int		light_params_read(t_rtui_min *win_lt, t_light *new)
{
	new->center.x = get_double(win_lt->en_x.text, '.');
	new->center.y = get_double(win_lt->en_y.text, '.');
	new->center.z = get_double(win_lt->en_z.text, '.');
	new->intensity = get_double(win_lt->en_intens.text, '.');
	new->type = POINT;
	new->next = NULL;
	return (0);
}

static	int		light_adding(t_rtui_min *win_lt, t_rt *rt, t_sdl *sdl)
{
	t_light	*new;

	if ((new = (t_light *)malloc(sizeof(*new))) == NULL)
	{
			ft_putendl(MEMORY);
			exit(1);
	}
	light_params_read(win_lt, new);
	push_back_light(&rt->head_light, new);
	create_img(rt, sdl);
	//here we will read entry.text
	return (0);
}

static	void	button_event_qlt(t_rtui_min *win_lt, t_rt *rt, t_sdl *sdl)
{
	if (kiss_button_event(&win_lt->button, &win_lt->e, &win_lt->draw))
	{
		if (light_adding(win_lt, rt, sdl))
			kiss_error("parameters are wrong!");
		win_lt->quit = 1;
	}
}

void			ui_win_lt_init(t_rtui_min *win_lt)
{
	win_lt->quit = 0;
	win_lt->draw = 1;
	kiss_array_new(&win_lt->objects);
	win_lt->renderer = kiss_init("light", &win_lt->objects, 300, 400);
	if (!win_lt->renderer)
		return ;
	kiss_window_new(&win_lt->window, NULL, 0, 0, 0, kiss_screen_width,
					kiss_screen_height);
	kiss_label_new(&win_lt->label_x, &win_lt->window, "enter x", 10, 5);
	kiss_label_new(&win_lt->label_y, &win_lt->window, "enter y", 10, 80);
	kiss_label_new(&win_lt->label_z, &win_lt->window, "enter z", 10, 155);
	kiss_label_new(&win_lt->label_intens, &win_lt->window, \
					"enter intensity", 8, 230);
	kiss_entry_new(&win_lt->en_x, &win_lt->window, 1, "", 10, 40, 280);
	kiss_entry_new(&win_lt->en_y, &win_lt->window, 1, "", 10, 115, 280);
	kiss_entry_new(&win_lt->en_z, &win_lt->window, 1, "", 10, 190, 280);
	kiss_entry_new(&win_lt->en_intens, &win_lt->window, 1, "", 10, 265, 280);
	kiss_button_new(&win_lt->button, &win_lt->window, "OK",
					win_lt->window.rect.w / 2 - kiss_normal.w / 2, 350);
	win_lt->window.visible = 1;
}

static	void	kiss_light_draw(t_rtui_min *win_lt)
{
	SDL_RenderClear(win_lt->renderer);
	kiss_window_draw(&win_lt->window, win_lt->renderer);
	kiss_label_draw(&win_lt->label_x, win_lt->renderer);
	kiss_label_draw(&win_lt->label_y, win_lt->renderer);
	kiss_label_draw(&win_lt->label_z, win_lt->renderer);
	kiss_label_draw(&win_lt->label_intens, win_lt->renderer);
	kiss_button_draw(&win_lt->button, win_lt->renderer);
	kiss_entry_draw(&win_lt->en_x, win_lt->renderer);
	kiss_entry_draw(&win_lt->en_y, win_lt->renderer);
	kiss_entry_draw(&win_lt->en_z, win_lt->renderer);
	kiss_entry_draw(&win_lt->en_intens, win_lt->renderer);
	kiss_button_draw(&win_lt->button, win_lt->renderer);
	SDL_RenderPresent(win_lt->renderer);
	win_lt->draw = 0;
}

int				kiss_light(t_rt *rt, t_sdl *sdl)
{
	t_rtui_min win_lt;

	ui_win_lt_init(&win_lt);
	while (!win_lt.quit)
	{
		SDL_Delay(10);
		while (SDL_PollEvent(&win_lt.e))
		{
			if (win_lt.e.type == SDL_QUIT)
				win_lt.quit = 1;
			kiss_window_event(&win_lt.window, &win_lt.e, &win_lt.draw);
			kiss_entry_event(&win_lt.en_x, &win_lt.e, &win_lt.draw);
			kiss_entry_event(&win_lt.en_y, &win_lt.e, &win_lt.draw);
			kiss_entry_event(&win_lt.en_z, &win_lt.e, &win_lt.draw);
			kiss_entry_event(&win_lt.en_intens, &win_lt.e, &win_lt.draw);
			button_event_qlt(&win_lt, rt, sdl);
		}
		if (!win_lt.draw)
			continue ;
		kiss_light_draw(&win_lt);
	}
	kiss_clean(&win_lt.objects);
	return (0);
}