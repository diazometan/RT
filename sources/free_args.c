/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 20:27:52 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/25 14:45:12 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	free_args(t_shape *shape, t_light *light, t_texture *texture)
{
	t_shape *tmp_shape;
	t_light *tmp_light;
	t_texture *tmp_texture;

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
		tmp_texture = texture;
		texture = texture->next;
		free(tmp_texture);
	}
}
