/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lighting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 13:51:26 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/13 11:27:01 by rgyles           ###   ########.fr       */
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

void			get_lighting(char *s, t_light **head)
{
	int		i;
	char	*start;
	char	*end;
	char	*object;
	char	*str;
	t_light	*new;

	(void)head;
	i = 1;
	while ((object = ft_strextract(s, '{', '}')) != NULL)
	{
		new = (t_light *)malloc(sizeof(*new));
		new->next = NULL;
		//printf("light %d - %s\n\n", i, object);
		start = ft_strstr(s, "type");
		start++;
		end = ft_strchr(start, ',');
		if (ft_strnstr(start, "point", end - start))
			new->type = POINT;
		else if (ft_strnstr(start, "directional", end - start))
			new->type = DIRECTIONAL;
		else if (ft_strnstr(start, "ambient", end - start))
			new->type = AMBIENT;
		else
		{
			ft_putendl("check config file for mistakes");
			exit(1);
		}
		start = ft_strstr(s, "intensity");
		if ((str = ft_strextract(start, ':', ',')) == NULL)
			str = ft_strextract(start, ':', '}');
		new->intensity = ft_atof(str);
		free(str);
		if (new->type == POINT)
		{
			start = ft_strstr(s, "center");
			str = ft_strextract(start, '[', ']');
			extract_coord(str, &new->point);
			free(str);
		}
		else if (new->type == DIRECTIONAL) //no more need to store in the same structure as point light sourcem check later!!!
		{
			start = ft_strstr(s, "direction");
			str = ft_strextract(start, '[', ']');
			extract_coord(str, &new->ray);
			free(str);
		}
		i++;
		s += ft_strlen(object);
		push_back_light(head, new);
	}
}
