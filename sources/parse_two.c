/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 10:26:44 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/18 11:09:38 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_direction(char *s, t_shape *new)
{
	char	*start;
	char	*str;
	t_coord	a;
	t_coord	b;

	if (new->figure != TRIANGLE)
	{
		start = ft_strstr(s, "direction");
		str = ft_strextract(start, '[', ']');
		extract_coord(str, &new->unit);
		free(str);
	}
	else
	{
		coord_add_subtract(&new->triangle[1], &new->triangle[0], &a, 1);
		coord_add_subtract(&new->triangle[2], &new->triangle[0], &b, 1);
		cross_product(&a, &b, &new->unit);
	}
	normalize_vector(&new->unit, vector_length(&new->unit));
}

void	init_radius(char *s, t_shape *new)
{
	char	*start;
	char	*str;

	if (new->figure == SPHERE || new->figure == CYLINDER || new->figure == DISK)
	{
		start = ft_strstr(s, "radius");
		if (start == NULL)
		{
			ft_putendl("\033[0;31mRadius is missing!\033[0m");
			ft_putendl("Please fix config file");
			exit(1);
		}
		if ((str = ft_strextract(start, ':', ',')) == NULL)
			str = ft_strextract(start, ':', '}');
		new->radius = ft_atof(str);
		free(str);
	}
}

void	init_angle(char *s, t_shape *new)
{
	char	*start;
	char	*str;

	if (new->figure == CONE)
	{
		if ((start = ft_strstr(s, "angle")) == NULL)
		{
			ft_putendl("\033[0;31mAngle is missing!\033[0m");
			ft_putendl("Please fix config file");
			exit(1);
		}
		if ((str = ft_strextract(start, ':', ',')) == NULL)
			str = ft_strextract(start, ':', '}');
		new->angle = (M_PI * ft_atof(str)) / 180;
		free(str);
	}
}

void	init_height(char *s, t_shape *new)
{
	char	*start;
	char	*str;

	if (new->figure == CONE || new->figure == CYLINDER)
	{
		if ((start = ft_strstr(s, "height")) == NULL)
		{
			ft_putendl("\033[0;31mHeight is missing!\033[0m");
			ft_putendl("Please fix config file");
			exit(1);
		}
		if ((str = ft_strextract(start, ':', ',')) == NULL)
			str = ft_strextract(start, ':', '}');
		new->h = ft_atof(str);
		free(str);
	}
}
