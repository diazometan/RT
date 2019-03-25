/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 12:35:37 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/25 13:51:34 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		push_back_texture(t_texture **head, t_texture *new)
{
	t_texture	*tmp;

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

static int	texture_check(char *name, t_shape *new, t_texture *head)
{
	while (head != NULL)
	{
		if (ft_strequ(head->name, name))
		{
			new->texture = head;
			return (0);
		}
		head = head->next;
	}
	return (1);
}

static t_texture	*create_texture(char *str, t_shape *shape)
{
	char		*file_name;
	t_texture	*new;

	new = (t_texture *)malloc(sizeof(*new));
	new->name = str;
	file_name = ft_memalloc(13 + ft_strlen(new->name));
	ft_strcpy(file_name, "textures/");
	ft_strcat(file_name, new->name);
	ft_strcat(file_name, ".bmp");
	if ((new->surface = SDL_LoadBMP(file_name)) == NULL)
	{
		ft_putendl("SDL_LoadBMP Error");
		exit(1);
	}
	new->pixel = (unsigned char *)new->surface->pixels;
	new->next = NULL;
	shape->texture = new;
	return (new);
}

int	init_texture(char *object, t_shape *shape, t_texture **head_textures)
{
	char	*start;
	char	*str;

	if ((start = ft_strstr(object, "texture")) != NULL)
	{
		str = ft_strextract(start + 8, '"', '"');
		if (texture_check(str, shape, *head_textures))
			push_back_texture(head_textures, create_texture(str, shape));
		else
			free(str);
		return (0);
	}
	return (1);
}
