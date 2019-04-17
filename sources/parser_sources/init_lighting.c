/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lighting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 18:55:04 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/17 10:01:35 by rgyles           ###   ########.fr       */
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

static void	init_intensity(char *s, double *intensity)
{
	if ((s = ft_strstr(s, "\"intensity\"")) == NULL || *(s + 11) != ':')
	{
		ft_putendl(LIGHT M_INT PFCF);
		exit(1);
	}
	else if ((*intensity = get_double(s + 12, ',')) < 0)
	{
		ft_putendl(LIGHT U_INT PFCF);
		exit(1);
	}
}

static int		identify_light(char *start)
{
	if (ft_strcequ(start, "\"point\"", ','))
		return (POINT);
	else if (ft_strcequ(start, "\"directional\"", ','))
		return (DIRECTIONAL);
	else if (ft_strcequ(start, "\"ambient\"", ','))
		return (AMBIENT);
	else if (ft_strcequ(start, "\"spot\"", ','))
		return (SPOT);
	else
		return (-1);
}

static void	init_fun_allocator(char *s, t_light *new)
{
	if (ft_strcequ(s, "\"type\"", ':') == 0)
	{
		ft_putendl(M_LIGHT PFCF);
		exit(1);
	}
	if ((new->type = identify_light(s + 7)) == -1)
	{
		ft_putendl(U_LIGHT PFCF);
		exit(1);
	}
	printf("type - %d\n", new->type);
	if (new->type != DIRECTIONAL && new->type != AMBIENT)
		init_center(s, &new->center);
	if (new->type != POINT && new->type != AMBIENT && new->type != DIRECTIONAL)
		init_direction(s, &new->dir, NULL);
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
			ft_putendl(M_COLOR PFCF);
			exit(1);
		}
		++s;
	}
}
