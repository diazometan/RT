/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lighting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 18:55:04 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/16 20:24:27 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		push_back_light(t_light **head, t_light *new)
{
	t_light	*tmp;

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

static void		get_light_type(char *object, t_light *new)
{
	int		len;
	char	*start;
	char	*end;

	start = ft_strstr(object, "type");
	end = ft_strchr(start, ',');
	len = end - start;
	if (ft_strnstr(start, "point", len))
		new->type = POINT;
	else if (ft_strnstr(start, "directional", len))
		new->type = DIRECTIONAL;
	else if (ft_strnstr(start, "ambient", len))
		new->type = AMBIENT;
	else if (ft_strnstr(start, "spot", len))
		new->type = SPOT;
	else
	{
		ft_putendl(U_LIGHT PFCF);
		exit(1);
	}
}

static void		get_intensity(char *object, t_light *new)
{
	char	*str;
	char	*start;

	start = ft_strstr(object, "intensity");
	if ((str = ft_strextract(start, ':', ',')) == NULL)
		str = ft_strextract(start, ':', '\0');
	if ((new->intensity = ft_atof(str)) > 2)
	{
		ft_putendl(U_INTENS PFCF);
		exit(1);
	}
	free(str);
}

static void		get_coordinates(char *object, t_light *new)
{
	char	*str;
	char	*start;

	if (new->type == POINT || new->type == SPOT)
	{
		if ((start = ft_strstr(object, "center")) == NULL)
		{
			ft_putendl(M_CENTER PFCF);
			exit(1);
		}
		str = ft_strextract(start, '[', ']');
		//extract_coord(str, &new->point);
	}
	else //no more need to store in the same structure as point light sourcem check later!!!
	{
		if ((start = ft_strstr(object, "direction")) == NULL)
		{
			ft_putendl(M_DIR PFCF);
			exit(1);
		}
		str = ft_strextract(start, '[', ']');
		//extract_coord(str, &new->ray);
	}
	if (new->type == SPOT)
	{
		if ((start = ft_strstr(object, "dir")) == NULL)
		{
			ft_putendl(M_CENTER PFCF);
			exit(1);
		}
		str = ft_strextract(start, '[', ']');
		//extract_coord(str, &new->dir);
		vec3_normalize(&new->dir, vec3_length(&new->dir));
	}
	free(str);
}

void			init_lighting(char *s, t_light **head)
{
	char	*object;
	t_light	*new;

	while ((object = ft_strextract(s, '{', '}')) != NULL)
	{
		new = (t_light *)malloc(sizeof(*new));
		new->next = NULL;
		get_light_type(object, new);
		get_intensity(object, new);
		if (new->type == POINT || new->type == DIRECTIONAL || new->type == SPOT)
			get_coordinates(object, new);
		free(object);
		s += ft_strlen(object);
		push_back_light(head, new);
	}
}

void	init_fun_allocator(char *s, t_light *new)
{
	if (ft_strcequ(s, "\"type\"", ':') == 0)
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

char			*init_lighting(char *s, t_light **head)
{
	t_light	*new;

	while (1)
	{
		if (*s != '{' || (end = get_end(s + 1, '{', '}')) == NULL)
			return (NULL);
		*end = '\0';
		if ((new = (t_light *)malloc(sizeof(*new))) == NULL)
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
