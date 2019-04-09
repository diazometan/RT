/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 10:26:44 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/09 13:04:36 by lwyl-the         ###   ########.fr       */
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
	else
		vec3_normalize(&new->unit, vec3_length(&new->unit));
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
