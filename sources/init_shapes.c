/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 18:54:37 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/02 19:01:31 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_center(char *s, t_shape *new)
{
	char	*start;
	char	*str;

	if ((start = ft_strstr(s, "center")) == NULL)
	{
		ft_putendl(M_CENTER PFCF);
		exit(1);
	}
	str = ft_strextract(start, '[', ']');
	extract_coord(str, &new->center);
	free(str);
}

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

void	init_shapes(char *s, t_shape **head, t_texture **head_textures)
{
	char	*object;
	t_shape	*new;

	while ((object = ft_strextract(s, '{', '}')) != NULL)
	{
		new = (t_shape *)malloc(sizeof(*new));
		new->next = NULL;
		init_shape_color(object, new);
		init_spec_refl(object, new);
		init_center(object, new);
		init_direction(object, new);
		init_radius(object, new);
		//init_angle(object, new);
		init_height(object, new);
		init_refraction(object, new);
		init_shape_function(new);
		if (init_texture(object, new, head_textures))
			new->texture = NULL;
		s += ft_strlen(object);
		free(object);
		push_back_shape(head, new);
	}
}
