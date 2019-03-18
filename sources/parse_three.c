/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 10:35:15 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/18 10:40:16 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_triangle(char *s, t_shape *new)
{
	char	*start;
	char	*str;

	start = ft_strstr(s, "A");
	str = ft_strextract(start, '[', ']');
	extract_coord(str, &new->triangle[0]);
	free(str);
	start = ft_strstr(s, "B");
	str = ft_strextract(start, '[', ']');
	extract_coord(str, &new->triangle[1]);
	free(str);
	start = ft_strstr(s, "C");
	str = ft_strextract(start, '[', ']');
	extract_coord(str, &new->triangle[2]);
	free(str);
	new->center.x = (new->triangle[0].x + new->triangle[1].x + new->triangle[2].x) / 3;
	new->center.y = (new->triangle[0].y + new->triangle[1].y + new->triangle[2].y) / 3;
	new->center.z = (new->triangle[0].z + new->triangle[1].z + new->triangle[2].z) / 3;
	coord_add_subtract(&new->triangle[2], &new->triangle[0], &new->abc[0], 1);
	coord_add_subtract(&new->triangle[1], &new->triangle[2], &new->abc[1], 1);
	coord_add_subtract(&new->triangle[0], &new->triangle[1], &new->abc[2], 1);
}

void	init_center(char *s, t_shape *new)
{
	char	*start;
	char	*str;

	if ((start = ft_strstr(s, "center")) == NULL)
	{
		ft_putendl("\033[0;31mCenter coordinates are missing!\033[0m");
		ft_putendl("Please fix config file");
		exit(1);
	}
	str = ft_strextract(start, '[', ']');
	extract_coord(str, &new->center);
	free(str);
}
