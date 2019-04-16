/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 18:54:37 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/16 19:51:47 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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

	//printf("identifying shape - %s\n", s + 8);
	//printf("dir - %.2f %.2f %.2f\n", new->center.x, new->center.y, new->center.z);
	//if (new->figure == SPHERE)
		//printf("radius - %f\n", new->dims.x);
	//printf("\nobject in fun_allocator - %s\n", s);
void	init_fun_allocator(char *s, t_shape *new, t_texture **head_textures)
{
	if (ft_strcequ(s, "\"shape\"", ':') == 0)
	{
		ft_putendl(M_SHAPE PFCF);
		exit(1);
	}
	if ((new->figure = identify_shape(s + 8)) == -1)
	{
		ft_putendl(U_SHAPE PFCF);
		exit(1);
	}
	identify_color(s, &new->color);
	init_center(s, &new->center);
	init_direction(s, &new->unit, &new->rotation);
	init_dimensions(s, new->figure, &new->dims);
	init_reflection(s, &new->reflection);
	init_refraction(s, &new->refraction);
	init_specular(s, &new->specular);
	init_function(new);
	init_function_texture(new);
	init_texture(s, new, head_textures);
	init_texture_map(s, new, head_textures);
}

char		*init_shapes(char *s, t_shape **head, t_texture **head_textures)
{
	t_shape	*new;

	while (1)
	{
		if (*s != '{' || (end = get_end(s + 1, '{', '}')) == NULL)
			return (NULL);
		*end = '\0';
		if ((new = (t_shape *)malloc(sizeof(*new))) == NULL)
		{
			ft_putendl(MEMORY);
			exit(1);
		}
		new->next = NULL;
		init_fun_allocator(s + 1, new, head_textures);
		s = end + 1;
		push_back_shape(head, new);
		if (*s == ']')
			return (s + 1);
		else if (*s != ',')
		{
			ft_putendl(M_COLOR PFCF);
			exit(1);
		}
		++s;
	}
}
