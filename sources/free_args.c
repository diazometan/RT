/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 20:27:52 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/22 20:21:28 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			exit_programm(t_rt *rt, t_sdl *sdl)
{
	free_args(rt->head_shapes, rt->head_light, rt->head_textures);
	SDL_FreeSurface(sdl->surf);
	free(sdl->img_data);
	SDL_DestroyWindow(sdl->win);
}

void			*check_memory(void *new)
{
	if (new == NULL)
	{
		ft_putendl(MEMORY);
		exit(1);
	}
	return (new);
}

void			free_args(t_shape *shape, t_light *light, t_texture *texture)
{
	t_shape		*tmp_shape;
	t_light		*tmp_light;
	t_texture	*tmp_texture;

	while (shape != NULL)
	{
		tmp_shape = shape;
		shape = shape->next;
		free(tmp_shape);
	}
	while (light != NULL)
	{
		tmp_light = light;
		light = light->next;
		free(tmp_light);
	}
	while (texture != NULL)
	{
		free(texture->name);
		SDL_FreeSurface(texture->surface);
		tmp_texture = texture;
		texture = texture->next;
		free(tmp_texture);
	}
}
