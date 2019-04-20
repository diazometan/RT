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

static void	vscrollbar1_event(kiss_vscrollbar *vscrollbar, SDL_Event *e,
								kiss_textbox *textbox1, int *draw)
{
	int firstline;

	if (kiss_vscrollbar_event(vscrollbar, e, draw) &&
		textbox1->array->length - textbox1->maxlines > 0)
	{
		firstline = (int)((textbox1->array->length -
							textbox1->maxlines) * vscrollbar->fraction + 0.5);
		if (firstline >= 0)
			textbox1->firstline = firstline;
		*draw = 1;
	}
}

static void	textbox1_event(kiss_textbox *textbox1, SDL_Event *e, t_rtui *ui)
{
	int index;

	if (kiss_textbox_event(textbox1, e, &ui->draw))
	{
		index = ui->textbox1.firstline + ui->textbox1.selectedline;
		if (ft_strcmp((char *)kiss_array_data(ui->textbox1.array, index), ""))
		{
			ui->textbox1.selectedline = -1;
			kiss_string_copy(ui->slash, KISS_MAX_LABEL, ui->buffer, "/");
			kiss_string_copy(ui->file_path, KISS_MAX_LABEL,
				ui->slash, (char *)kiss_array_data(ui->textbox1.array, index));
			kiss_string_copy(ui->label_sel.text, KISS_MAX_LABEL,
				(char *)kiss_array_data(ui->textbox1.array, index), NULL);
			kiss_chdir((char *)kiss_array_data(ui->textbox1.array, index));
			if (ui->file_path[ft_strlen(ui->file_path) - 1] == '/')
				dirent_read(ui);
			ui->draw = 1;
		}
	}
}

static void	button_light_ambient(t_rtui *ui, t_rt *rt, t_sdl *sdl)
{
	if (kiss_button_event(&ui->button_ambient, &ui->e, &ui->draw))
	{
		kiss_ambient(rt, sdl);
	}
}

static void	ui_drawing(t_rtui *ui, t_rt *rt)
{
	SDL_RenderClear(ui->renderer);
	kiss_window_draw(&ui->window1, ui->renderer);
	kiss_textbox_draw(&ui->textbox1, ui->renderer);
	kiss_vscrollbar_draw(&ui->vscrollbar1, ui->renderer);
	kiss_label_draw(&ui->label_sel, ui->renderer);
	if (rt->win_width)
	{
		kiss_button_draw(&ui->button_hide, ui->renderer);
		kiss_button_draw(&ui->button_light, ui->renderer);
		kiss_button_draw(&ui->button_ambient, ui->renderer);
	}
	kiss_button_draw(&ui->button_ex, ui->renderer);
	kiss_button_draw(&ui->button_ok1, ui->renderer);
	SDL_RenderPresent(ui->renderer);
	ui->draw = 0;
}

int			ui_main(t_rt *rt, t_sdl *sdl)
{
	t_rtui ui;

	ui_init(&ui);
	while (!ui.quit)
	{
		while (SDL_PollEvent(&ui.e))
		{
			if (ui.e.type == SDL_QUIT)
				ui.quit = 1;
			kiss_window_event(&ui.window1, &ui.e, &ui.draw);
			vscrollbar1_event(&ui.vscrollbar1, &ui.e, &ui.textbox1, &ui.draw);
			textbox1_event(&ui.textbox1, &ui.e, &ui);
			button_light_ambient(&ui, rt, sdl);
			button_events_main(&ui, rt, sdl);
		}
		vscrollbar1_event(&ui.vscrollbar1, NULL, &ui.textbox1, &ui.draw);
		if (!ui.draw)
			continue ;
		ui_drawing(&ui, rt);
	}
	kiss_clean(&ui.objects);
	return (0);
}
