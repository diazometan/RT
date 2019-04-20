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

void	button_event(kiss_button *button, SDL_Event *e, int *draw, int *quit)
{
	if (kiss_button_event(button, e, draw))
		*quit = 1;
}

void	ui_min_init(t_rtui_min *min)
{
	min->quit = 0;
	min->draw = 1;
	kiss_array_new(&min->objects);
	min->renderer = kiss_init("ERROR", &min->objects, 320, 120);
	if (!min->renderer)
		return ;
	kiss_window_new(&min->window, NULL, 0, 0, 0, kiss_screen_width,
					kiss_screen_height);
	kiss_label_new(&min->label, &min->window, min->message, \
		min->window.rect.w / 2 - strlen(min->message) * \
		kiss_textfont.advance / 2, \
		min->window.rect.h / 2 - (kiss_textfont.fontheight\
		+ 2 * kiss_normal.h) / 2); 
	min->label.textcolor.r = 255;
	kiss_button_new(&min->button, &min->window, "OK",
			min->window.rect.w / 2 - kiss_normal.w / 2, \
			min->label.rect.y + kiss_textfont.fontheight + kiss_normal.h);
	min->window.visible = 1;
}

int		kiss_error(char *mes)
{
	t_rtui_min	min;

	ft_strcpy(min.message, mes);
	ui_min_init(&min);
	while (!min.quit)
	{
		SDL_Delay(10);
		while (SDL_PollEvent(&min.e))
		{
			if (min.e.type == SDL_QUIT)
				min.quit = 1;
			kiss_window_event(&min.window, &min.e, &min.draw);
			button_event(&min.button, &min.e, &min.draw, &min.quit);
		}
		if (!min.draw)
			continue;
		SDL_RenderClear(min.renderer);
		kiss_window_draw(&min.window, min.renderer);
		kiss_label_draw(&min.label, min.renderer);
		kiss_button_draw(&min.button, min.renderer);
		SDL_RenderPresent(min.renderer);
		min.draw = 0;
	}
	kiss_clean(&min.objects);
	return (0);
}
