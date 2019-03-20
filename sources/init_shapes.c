/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 18:54:37 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/20 09:57:55 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		push_back_shape(t_shape **head, t_shape *new)
{
	t_shape	*tmp;

	if (*head == NULL)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	init_shapes(char *s, t_shape **head)
{
	char	*object;
	t_shape	*new;

	while ((object = ft_strextract(s, '{', '}')) != NULL)
	{
		new = (t_shape *)malloc(sizeof(*new));
		new->next = NULL;
		init_shape_color(object, new);
		init_spec_refl(object, new);
		if (new->figure == TRIANGLE)
			init_triangle(object, new);
		else
			init_center(object, new);
		init_direction(object, new);
		init_radius(object, new);
		init_angle(object, new);
		init_height(object, new);
		init_refraction(object, new);
		s += ft_strlen(object);
		free(object);
		push_back_shape(head, new);
	}
}
