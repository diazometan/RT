/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 12:35:37 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/21 14:06:44 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			push_back_texture(t_texture **head, t_texture *new)
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

static int			texture_check(char *name, t_shape *new,
									t_texture *head, int normal)
{
	while (head != NULL)
	{
		if (ft_strequ(head->name, name))
		{
			if (normal)
				new->tex_normal = head;
			else
				new->texture = head;
			return (0);
		}
		head = head->next;
	}
	return (1);
}

static t_texture	*create_texture(char *str, t_shape *shape, int normal)
{
	char		*file_name;
	t_texture	*new;

	new = (t_texture *)malloc(sizeof(*new));
	new->name = str;
	if ((file_name = ft_memalloc(14 + ft_strlen(new->name))) == NULL)
	{
		ft_putendl(MEMORY);
		exit(1);
	}
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
	if (normal)
		shape->tex_normal = new;
	else
		shape->texture = new;
	return (new);
}

void				init_texture(char *s, t_shape *new,
									t_texture **head_textures)
{
	char	*str;

	if ((s = ft_strstr(s, "\"texture\"")) != NULL)
	{
		if (*(s + 9) != ':')
		{
			ft_putendl(U_TEX);
			exit(1);
		}
		if ((str = str_extract(s + 10, '"', '"')) == NULL)
		{
			ft_putendl(MEMORY);
			exit(1);
		}
		if ((new->effect_type = effect_check(str)))
			free(str);
		else if (texture_check(str, new, *head_textures, 0))
			push_back_texture(head_textures, create_texture(str, new, 0));
		else
			free(str);
		init_texture_displace(s, &new->t_dims);
		init_texture_division(s, &new->t_dims.z);
	}
	else
		new->texture = NULL;
}

void				init_texture_map(char *s, t_shape *new,
										t_texture **head_textures)
{
	char	*str;

	if ((s = ft_strstr(s, "\"normal_mapping\"")) != NULL)
	{
		if (*(s + 16) != ':')
		{
			ft_putendl(U_TEX);
			exit(1);
		}
		if ((str = str_extract(s + 17, '"', '"')) == NULL)
		{
			ft_putendl(MEMORY);
			exit(1);
		}
		if (texture_check(str, new, *head_textures, 1))
			push_back_texture(head_textures, create_texture(str, new, 1));
		else
			free(str);
	}
	else
		new->tex_normal = NULL;
}
