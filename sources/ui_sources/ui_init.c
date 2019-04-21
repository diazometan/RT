/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 19:05:24 by jfrankly          #+#    #+#             */
/*   Updated: 2019/04/18 19:05:25 by jfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ui_init_2(t_rtui *ui)
{
	kiss_vscrollbar_new(&ui->vscrollbar1, &ui->window1, \
						ui->textbox1.rect.x + ui->textbox_width,
						ui->textbox1.rect.y, ui->textbox_height);
	kiss_label_new(&ui->label_sel, &ui->window1, "Choose file", \
					ui->textbox1.rect.x + kiss_edge, ui->textbox1.rect.y +
					ui->textbox_height + kiss_normal.h);
	kiss_button_new(&ui->button_ok1, &ui->window1, "render",
					ui->window1.rect.w / 2 - kiss_normal.w / 2 - 20, 520);
	kiss_button_new(&ui->button_hide, &ui->window1, "hide",
					ui->window1.rect.w / 2 - kiss_normal.w / 2 - 90, 460);
	kiss_button_new(&ui->button_save, &ui->window1, "save",
					ui->window1.rect.w / 2 - kiss_normal.w / 2 + 50, 460);
	kiss_button_new(&ui->button_light, &ui->window1, "light",
					ui->window1.rect.w / 2 - kiss_normal.w / 2 - 90, 490);
	kiss_button_new(&ui->button_ambient, &ui->window1, "ambient",
					ui->window1.rect.w / 2 - kiss_normal.w / 2 + 50, 490);
	kiss_button_new(&ui->button_ex, &ui->window1, "exit",
					ui->window1.rect.w / 2 - kiss_normal.w / 2 - 20, 550);
	dirent_read(ui);
	ui->window1.visible = 1;
}

void	ui_init(t_rtui *ui)
{
	ui->textbox_width = 350;
	ui->textbox_height = 300;
	ui->window2_width = 200;
	ui->window2_height = 168;
	ui->quit = 0;
	ui->draw = 1;
	ui->renderer = kiss_init("RT", &ui->objects, 400, 600);
	if (!ui->renderer)
		return ;
	kiss_array_new(&ui->a1);
	kiss_array_append(&ui->objects, ARRAY_TYPE, &ui->a1);
	kiss_window_new(&ui->window1, NULL, 1, 0, 0,
					kiss_screen_width, kiss_screen_height);
	ui->label.textcolor.r = 255;
	kiss_textbox_new(&ui->textbox1, &ui->window1, 1, &ui->a1, 30,
					3 * kiss_normal.h, ui->textbox_width, ui->textbox_height);
	ui_init_2(ui);
}
