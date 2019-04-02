/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 10:26:44 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/02 21:39:01 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_direction(char *s, t_shape *new)
{
	char	*start;
	char	*str;
	//t_vec3	a;
	//t_vec3	b;

	if ((start = ft_strstr(s, "direction")) == NULL)
	{
		ft_putendl(M_DIR PFCF);
		exit(1);
	}
	str = ft_strextract(start, '[', ']');
	extract_coord(str, &new->unit);
	free(str);
	if (new->figure != PLANE)
	{
		new->unit.x = M_PI * new->unit.x/ 180;
		new->unit.y = M_PI * new->unit.y/ 180;
		new->unit.z = M_PI * new->unit.z/ 180;
	}
	//else
		//vec3_normalize(&new->unit, vec3_length(&new->unit));
}

void	init_radius(char *s, t_shape *new)
{
	char	*start;
	char	*str;

	if (new->figure == SPHERE || new->figure == CYLINDER || new->figure == DISK || new->figure == CONE || new->figure == BOX ||
		new->figure == CAPSULE)
	{
		start = ft_strstr(s, "radius");
		if (start == NULL)
		{
			ft_putendl(M_RADIUS PFCF);
			exit(1);
		}
		if ((str = ft_strextract(start, ':', ',')) == NULL)
			str = ft_strextract(start, ':', '\0');
		new->radius = ft_atof(str);
		free(str);
	}
}

void	init_height(char *s, t_shape *new)
{
	char	*start;
	char	*str;

	if (new->figure == CONE || new->figure == CYLINDER || new->figure == CAPSULE)
	{
		if ((start = ft_strstr(s, "height")) == NULL)
		{
			ft_putendl(M_HEIGHT PFCF);
			exit(1);
		}
		if ((str = ft_strextract(start, ':', ',')) == NULL)
			str = ft_strextract(start, ':', '\0');
		new->h = ft_atof(str);
		free(str);
	}
}

void	init_refraction(char *s, t_shape *new)
{
	char	*start;
	char	*str;

	if ((start = ft_strstr(s, "refraction")) == NULL)
		new->refract = 0;
	else
	{
		if ((str = ft_strextract(start, ':', ',')) == NULL)
			str = ft_strextract(start, ':', '\0');
		new->refract = ft_atof(str);
		free(str);
		if (new->refract < 1)
		{
			ft_putendl(U_REFRACT PFCF);
			exit(1);
		}
	}
}
