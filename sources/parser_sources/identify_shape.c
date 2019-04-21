/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_shape.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 13:11:24 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/21 13:04:09 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	identify_operation(char *start)
{
	if (strcequ(start, "\"unite\"", ','))
		return (UNITE);
	else if (strcequ(start, "\"intersect\"", ','))
		return (INTERSECT);
	else if (strcequ(start, "\"difference\"", ','))
		return (DIFFERENCE);
	else if (strcequ(start, "\"blend\"", ','))
		return (BLEND);
	else if (strcequ(start, "\"mix\"", ','))
		return (MIX);
	else
		return (-1);
}

static int	identify_shape(char *start)
{
	if (strcequ(start, "\"plane\"", ','))
		return (PLANE);
	else if (strcequ(start, "\"sphere\"", ','))
		return (SPHERE);
	else if (strcequ(start, "\"cylinder\"", ','))
		return (CYLINDER);
	else if (strcequ(start, "\"infinite_cylinder\"", ','))
		return (INF_CYLINDER);
	else if (strcequ(start, "\"cone\"", ','))
		return (CONE);
	else if (strcequ(start, "\"infinite_cone\"", ','))
		return (INF_CONE);
	else if (strcequ(start, "\"torus\"", ','))
		return (TORUS);
	else if (strcequ(start, "\"capsule\"", ','))
		return (CAPSULE);
	else if (strcequ(start, "\"box\"", ','))
		return (BOX);
	else if (strcequ(start, "\"elipsoid\"", ','))
		return (ELIPSIOD);
	else if (strcequ(start, "\"fractal\"", ','))
		return (FRACTAL);
	else
		return (identify_operation(start));
}

void		identify_object(char *s, int *figure)
{
	if ((s = strstr(s, "\"shape\"")) == NULL || *(s + 7) != ':')
	{
		ft_putendl(M_SHAPE);
		exit(1);
	}
	if ((*figure = identify_shape(s + 8)) == -1)
	{
		ft_putendl(U_SHAPE);
		exit(1);
	}
}
