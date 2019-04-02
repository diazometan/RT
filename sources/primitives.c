/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 17:49:53 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/01 18:00:08 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double			gd_sphere(t_coord *p, t_shape *shape)
{
	t_coord orig;

	coord_add_subtract(p, &shape->center, &orig, 1);
	return (vector_length(&orig) - shape->radius);
}

double			gd_plane(t_coord *p, t_shape *shape)
{
	t_coord orig;

	coord_add_subtract(p, &shape->center, &orig, 1);
	return (dot_product(&shape->unit, &tmp));
}

double			gd_cylinder(t_coord *p, t_shape *shape)
{
	t_coord orig;

	coord_add_subtract(p, &shape->center, &orig, 1);
	return (sqrt(orig.x * orig.x + orig.z * orig.z) - shape->radius);
}

double			gd_cone(t_coord *p, t_shape *shape)
{
	t_coord d;
	t_coord dimension;
	t_coord tmp;
	double len;
	double distance;

	coord_add_subtract(p, &shape->center, &d, 1);
	len = sqrt(d.x * d.x + d.z * d.z);
	dimension.x = 1.0;//shape->radius;
	dimension.y = shape->h;
	//printf("h - %f\n", shape->radius);
	dimension.z = 0;

	tmp.x = len;
	tmp.y = d.y;
	tmp.z = 0;
	normalize_vector(&dimension, vector_length(&dimension));
	//printf("x1 - %f y1 - %f\n", dimension.x, dimension.y);
	distance = dot_product(&dimension, &tmp);

	//printf("dist - %f\n", distance);
	return (distance);
}
