/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dimensions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:37:02 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/03 13:56:17 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	init_radius(char *s, t_shape *new)
{
	char	*start;
	char	*str;

	start = ft_strstr(s, "radius");
	if (start == NULL)
	{
		ft_putendl(M_RADIUS PFCF);
		exit(1);
	}
	if ((str = ft_strextract(start, ':', ',')) == NULL)
		str = ft_strextract(start, ':', '\0');
	new->dims.x = ft_atof(str);
	free(str);
}

static void	init_radius_torus(char *s, t_shape *new)
{
	char	*start;
	char	*str;

	if ((start = ft_strstr(s, "inner_radius")) == NULL)
	{
		ft_putendl(M_HEIGHT PFCF);
		exit(1);
	}
	if ((str = ft_strextract(start, ':', ',')) == NULL)
		str = ft_strextract(start, ':', '\0');
	new->dims.x = ft_atof(str);
	free(str);
	if ((start = ft_strstr(s, "outer_radius")) == NULL)
	{
		ft_putendl(M_HEIGHT PFCF);
		exit(1);
	}
	if ((str = ft_strextract(start, ':', ',')) == NULL)
		str = ft_strextract(start, ':', '\0');
	new->dims.y = ft_atof(str);
	free(str);
}

static void	init_height(char *s, t_shape *new)
{
	char	*start;
	char	*str;

	if ((start = ft_strstr(s, "height")) == NULL)
	{
		ft_putendl(M_HEIGHT PFCF);
		exit(1);
	}
	if ((str = ft_strextract(start, ':', ',')) == NULL)
		str = ft_strextract(start, ':', '\0');
	new->dims.y = ft_atof(str);
	free(str);
}

void		init_dimensions(char *s, t_shape *new)
{
	if (new->figure == SPHERE)
		init_radius(s, new);
	else if (new->figure == CONE || new->figure == CYLINDER || new->figure == CAPSULE)
	{
		init_radius(s, new);
		init_height(s, new);
	}
	else if (new->figure == TORUS)
		init_radius_torus(s, new);
}
