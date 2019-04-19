/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lighting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 18:55:04 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/19 11:24:53 by rgyles           ###   ########.fr       */
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

static void		init_intensity(char *s, double *intensity)
{
	if ((s = ft_strstr(s, "\"intensity\"")) == NULL || *(s + 11) != ':')
	{
		ft_putendl(M_INT);
		exit(1);
	}
	if ((*intensity = get_double(s + 12, ',')) < 0)
	{
		ft_putendl(U_INT);
		exit(1);
	}
}

static int		identify_light(char *start)
{
	if (strcequ(start, "\"point\"", ','))
		return (POINT);
	else if (strcequ(start, "\"directional\"", ','))
		return (DIRECTIONAL);
	else if (strcequ(start, "\"ambient\"", ','))
		return (AMBIENT);
	else if (strcequ(start, "\"spot\"", ','))
		return (SPOT);
	else
		return (-1);
}

static void		init_fun_allocator(char *s, t_light *new)
{
	if (strcequ(s, "\"type\"", ':') == 0)
	{
		ft_putendl(M_LIGHT);
		exit(1);
	}
	if ((new->type = identify_light(s + 7)) == -1)
	{
		ft_putendl(U_LIGHT);
		exit(1);
	}
	if (new->type != DIRECTIONAL && new->type != AMBIENT)
		init_center(s, &new->center);
	if (new->type == SPOT)
	{
		init_direction(s, &new->dir, NULL);
		init_view_angle(s, &new->angle);
	}
	else if (new->type == DIRECTIONAL)
		init_direction(s, &new->ray, NULL);
	init_intensity(s, &new->intensity);
	new->next = NULL;
}

char			*init_lighting(char *s, t_light **head)
{
	char	*end;
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
		init_fun_allocator(s + 1, new);
		s = end + 1;
		push_back_light(head, new);
		if (*s == ']')
			return (s + 1);
		else if (*s != ',')
		{
			ft_putendl(M_LIGHT);
			exit(1);
		}
		++s;
	}
}
