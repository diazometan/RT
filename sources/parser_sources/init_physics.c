/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_physics.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 13:44:28 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/17 20:11:14 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	init_reflection_depth(char *s, int *depth)
{
	if ((s = ft_strstr(s, "\"reflection_depth\"")) == NULL || *(s + 18) != ':')
	{
		ft_putendl(M_DEPTH);
		exit(1);
	}
	else if ((*depth = (int)get_double(s + 19, ',')) < 0 || *depth > 5)
	{
		ft_putendl(U_DEPTH);
		exit(1);
	}
}

static void	init_pixel_division(char *s, int *p_division)
{
	if ((s = ft_strstr(s, "\"pixel_division\"")) == NULL || *(s + 16) != ':')
	{
		ft_putendl(M_PDIV);
		exit(1);
	}
	else if ((*p_division = (int)get_double(s + 17, ',')) < 0 ||
													*p_division > 5)
	{
		ft_putendl(U_PDIV);
		exit(1);
	}
}

int			init_physics(char *s, t_rt *rt)
{
	char	*end;

	if ((s = ft_strnstr(s, "\"physics\":", 10)) == NULL)
		return (1);
	s += 10;
	if (*s != '{' || (end = get_end(s++ + 1, '{', '}')) == NULL ||
													*(end + 1) != '}')
	{
		ft_putendl(M_MATCH);
		return (1);
	}
	*end = '\0';
	init_pixel_division(s, &rt->p_division);
	init_reflection_depth(s, &rt->depth);
	rt->sample_step = 1.0 / rt->p_division;
	rt->sample_center = rt->sample_step / 2.0;
	return (0);
}
