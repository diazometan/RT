/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 20:27:52 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/11 19:17:44 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	free_args(t_shape *shape, t_light *light)
{
	t_shape *tmp_shape;
	t_light *tmp_light;

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
}
