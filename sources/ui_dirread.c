/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_dirread.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 19:05:10 by jfrankly          #+#    #+#             */
/*   Updated: 2019/04/18 19:05:12 by jfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kiss_sdl.h"
#include "rt.h"

static void	text_reset(kiss_textbox *textbox, kiss_vscrollbar *vscrollbar)
{
	qsort(textbox->array->data, textbox->array->length, sizeof(void *),
				kiss_string_compare);
	vscrollbar->step = 0.;
	if (textbox->array->length - textbox->maxlines > 0)
		vscrollbar->step = 1. / (textbox->array->length -
		textbox->maxlines);
	textbox->firstline = 0;
	textbox->highlightline = -1;
	vscrollbar->fraction = 0.;
}

void		dirent_read(t_rtui *ui)
{
	kiss_dirent		*ent;
	kiss_stat		s;
	kiss_dir		*dir;
	char			ending[2];

	kiss_array_free(ui->textbox1.array);
	kiss_array_new(ui->textbox1.array);
	kiss_getcwd(ui->buffer, KISS_MAX_LENGTH);
	ft_strcpy(ending, "/");
	if (!(ft_strcmp(ui->buffer, "/")))
		ft_strcpy(ending, "");
	dir = kiss_opendir(".");
	while ((ent = kiss_readdir(dir)))
	{
		if (!ent->d_name)
			continue;
		kiss_getstat(ent->d_name, &s);
		if (kiss_isdir(s))
			kiss_array_appendstring(ui->textbox1.array, 0, ent->d_name, "/");
		if (kiss_isreg(s))
			kiss_array_appendstring(ui->textbox1.array, 0, ent->d_name, NULL);
	}
	kiss_closedir(dir);
	text_reset(&ui->textbox1, &ui->vscrollbar1);
}
