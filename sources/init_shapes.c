/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 18:54:37 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/05 17:04:35 by lwyl-the         ###   ########.fr       */
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

void	push_back_shape(t_shape **head, t_shape *new)
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

void	init_rotation(t_shape *new)
{
	new->rotation = matrix_multiply(inverse_x_rotate(new->unit.x),
							matrix_multiply(inverse_y_rotate(new->unit.y), inverse_z_rotate(new->unit.z)));
}

void	init_shapes(char *s, t_shape **head, t_texture **head_textures)
{
	char	*object;
	t_shape	*new;

	while ((object = ft_strextract(s, '{', '}')) != NULL) //need extra check - segfault when extra spaces after object
	{
		new = (t_shape *)malloc(sizeof(*new));
		new->next = NULL;
		init_shape_color(object, new);
		if (new->color == YELLOW)
			new->emission = 0.2;
		else
			new->emission = 0.0;
		init_spec_refl(object, new);
		init_center(object, new);
		init_direction(object, new);
		init_rotation(new);
		init_dimensions(object, new);
		//init_radius(object, new);
		//init_height(object, new);
		init_refraction(object, new);
		init_function(new);
		if (init_texture(object, new, head_textures))
			new->texture = NULL;
		s += ft_strlen(object);
		free(object);
		push_back_shape(head, new);
	}
}
