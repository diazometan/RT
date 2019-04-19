/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dimensions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:37:02 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/19 10:15:42 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	init_radius(char *s, t_vec3 *dims)
{
	if ((s = ft_strstr(s, "\"radius\"")) == NULL || *(s + 8) != ':')
	{
		ft_putendl(M_RADIUS);
		exit(1);
	}
	if ((dims->x = get_double(s + 9, ',')) < 0)
	{
		ft_putendl(U_RADIUS);
		exit(1);
	}
}

static void	init_radius_two(char *s, t_vec3 *dims)
{
	char	*str;

	if ((str = ft_strstr(s, "\"radius_in\"")) == NULL || *(str + 11) != ':')
	{
		ft_putendl(M_IRADIUS);
		exit(1);
	}
	if ((dims->x = get_double(str + 12, ',')) < 0)
	{
		ft_putendl(M_IRADIUS);
		exit(1);
	}
	if ((str = ft_strstr(s, "\"radius_out\"")) == NULL || *(str + 12) != ':')
	{
		ft_putendl(M_ORADIUS);
		exit(1);
	}
	if ((dims->y = get_double(str + 13, ',')) < 0)
	{
		ft_putendl(M_ORADIUS);
		exit(1);
	}
}

static void	init_height(char *s, t_vec3 *dims)
{
	if ((s = ft_strstr(s, "\"height\"")) == NULL || *(s + 8) != ':')
	{
		ft_putendl(M_HEIGHT);
		exit(1);
	}
	if ((dims->z = get_double(s + 9, ',')) < 0)
	{
		ft_putendl(U_HEIGHT);
		exit(1);
	}
}

static void	init_sides(char *s, t_vec3 *dims)
{
	if ((s = ft_strstr(s, "\"sides\"")) == NULL || *(s + 7) != ':')
	{
		ft_putendl(M_SIDES);
		exit(1);
	}
	get_vector(s + 8, dims);
	if (dims->x < 0 || dims->y < 0 || dims->z < 0)
	{
		ft_putendl(U_SIDES);
		exit(1);
	}
}

void		init_dimensions(char *s, int figure, t_vec3 *dims)
{
	if (figure == SPHERE)
		init_radius(s, dims);
	else if (figure == CYLINDER || figure == CAPSULE)
	{
		init_radius(s, dims);
		init_height(s, dims);
	}
	else if (figure == CONE)
		init_height(s, dims);
	else if (figure == BOX || figure == ELIPSIOD || figure == FRACTAL)
		init_sides(s, dims);
	if (figure == TORUS || figure == CONE)
		init_radius_two(s, dims);
}
