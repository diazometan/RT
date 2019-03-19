/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_physics.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 17:26:15 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/19 11:36:03 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	init_reflection_depth(char *s, int *depth)
{
	char	*start;
	char	*str;

	if ((start = ft_strstr(s, "reflection depth")) == NULL)
	{
		ft_putendl(M_DEPTH PFCF);
		exit(1);
	}
	if ((str = ft_strextract(start, ':', ',')) == NULL)
		str = ft_strextract(start, ':', '\0');
	*depth = ft_atoi(str);
	free(str);
}

static void	init_pixel_division(char *s, int *p_division)
{
	char	*start;
	char	*str;

	if ((start = ft_strstr(s, "pixel division")) == NULL)
	{
		ft_putendl(M_PDIV PFCF);
		exit(1);
	}
	if ((str = ft_strextract(start, ':', ',')) == NULL)
		str = ft_strextract(start, ':', '\0');
	*p_division = ft_atoi(str);
	free(str);
}

void	init_physics(char *s, t_rt *rt)
{
	init_reflection_depth(s, &rt->depth);
	if (rt->depth > 4)
	{
		ft_putendl(U_DEPTH PFCF);
		exit(1);
	}
	init_pixel_division(s, &rt->p_division);
	if (rt->p_division > 8)
	{
		ft_putendl(U_PDIV PFCF);
		exit(1);
	}
	rt->sample_step = 1.0 / rt->p_division;
	rt->sample_center = rt->sample_step / 2.0;
}
