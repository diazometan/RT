/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lighting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 18:55:04 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/18 15:35:12 by rgyles           ###   ########.fr       */
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

	if (new->type == POINT)
	{
		if ((start = ft_strstr(object, "center")) == NULL)
		{
			ft_putendl(M_CENTER PFCF);
			exit(1);
		}
		str = ft_strextract(start, '[', ']');
		extract_coord(str, &new->point);
	}
	else //no more need to store in the same structure as point light sourcem check later!!!
	{
		if ((start = ft_strstr(object, "direction")) == NULL)
		{
			ft_putendl(M_DIR PFCF);
			exit(1);
		}
		str = ft_strextract(start, '[', ']');
		extract_coord(str, &new->ray);
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
		if (new->type == POINT || new->type == DIRECTIONAL)
			get_coordinates(object, new);
		free(object);
		s += ft_strlen(object);
		push_back_light(head, new);
	}
}
