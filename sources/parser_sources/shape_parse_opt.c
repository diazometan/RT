/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_parse_opt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 15:50:02 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/17 16:04:41 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_refraction(char *s, double *refraction)
{
	if ((s = ft_strstr(s, "\"refraction\"")) == NULL)
		*refraction = 0.0;
	else if (*(s + 12) != ':')
	{
		ft_putendl(M_REFR);
		exit(1);
	}
	else if ((*refraction = get_double(s + 13, ',')) < 0)
	{
		ft_putendl(U_REFR);
		exit(1);
	}
}

void	init_reflection(char *s, double *reflection)
{
	if ((s = ft_strstr(s, "\"reflection\"")) == NULL)
		*reflection = 0.0;
	else if (*(s + 12) != ':')
	{
		ft_putendl(M_REFL);
		exit(1);
	}
	else if ((*reflection = get_double(s + 13, ',')) < 0)
	{
		ft_putendl(U_REFL);
		exit(1);
	}
}

void	init_specular(char *s, double *specular)
{
	if ((s = ft_strstr(s, "\"specular\"")) == NULL)
		*specular = 0.0;
	else if (*(s + 10) != ':')
	{
		ft_putendl(M_SPEC);
		exit(1);
	}
	else if ((*specular = get_double(s + 11, ',')) < 0)
	{
		ft_putendl(U_SPEC);
		exit(1);
	}
}
