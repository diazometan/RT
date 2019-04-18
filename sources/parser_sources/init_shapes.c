/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 18:54:37 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/18 20:06:14 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	push_back_shape(t_shape **head, t_shape *new)
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

static void	form_shape(char *s, t_shape *new, t_texture **head_textures)
{
	init_center(s, &new->center);
	init_direction(s, &new->unit, &new->rotation);
	init_dimensions(s, new->figure, &new->dims);
	init_texture(s, new, head_textures);
	init_texture_map(s, new, head_textures);
}

static void	form_group(char *s, t_shape *new, t_shape **head)
{
	new->child_one = find_child(s, "\"child_one\"", head);
	new->child_two = find_child(s, "\"child_two\"", head);
	new->child_one->child = 1;
	new->child_two->child = 1;
	new->group = 1;
	new->texture = NULL;
	new->tex_normal = NULL;
}

static void	init_fun_allocator(char *s, t_shape *new, t_shape **head,
								t_texture **head_textures)
{
	if ((s = strstr(s, "\"shape\"")) == NULL || *(s + 7) != ':')
	{
		ft_putendl(M_SHAPE);
		exit(1);
	}
	if ((new->figure = identify_shape(s + 8)) == -1)
	{
		ft_putendl(U_SHAPE);
		exit(1);
	}
	new->group = 0;
	new->child = 0;
	init_id(s, &new->id);
	identify_color(s, &new->color);
	init_reflection(s, &new->reflection);
	init_refraction(s, &new->refraction);
	init_specular(s, &new->specular);
	init_function(new);
	init_function_texture(new);
	if (new->figure > 0 && new->figure < 12)
		form_shape(s, new, head_textures);
	else
		form_group(s, new, head);
	new->next = NULL;
	push_back_shape(head, new);
}

char		*init_shapes(char *s, t_shape **head, t_texture **head_textures)
{
	char	*end;
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
		init_fun_allocator(s + 1, new, head, head_textures);
		s = end + 1;
		if (*s == ']')
			return (s + 1);
		else if (*s != ',')
		{
			ft_putendl(M_SHAPE);
			exit(1);
		}
		++s;
	}
}
