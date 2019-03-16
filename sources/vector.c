/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 16:38:45 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/15 10:41:50 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	dot_product(t_coord *a, t_coord *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

void	cross_product(t_coord *a, t_coord *b, t_coord *c)
{
	c->x = a->y * b->z - a->z * b->y;
	c->y = a->z * b->x - a->x * b->z;
	c->z = a->x * b->y - a->y * b->x;
}

void	scalar_product(t_coord *a, double number)
{
	a->x *= number;
	a->y *= number;
	a->z *= number;
}

double	vector_length(t_coord *vector)
{
	return (sqrt(pow(vector->x, 2) + pow(vector->y, 2) + pow(vector->z, 2)));
}

void	normalize_vector(t_coord *vector, double length)
{
	vector->x /= length;
	vector->y /= length;
	vector->z /= length;
}

void	get_intersection_point(t_coord *source, t_coord *ray, double t, t_coord *p)
{
	p->x = source->x + t * ray->x;
	p->y = source->y + t * ray->y;
	p->z = source->z + t * ray->z;
}

void	coord_add_subtract(t_coord *a, t_coord *b, t_coord *result, int flag)
{
	if (flag)
	{
		result->x = a->x - b->x;
		result->y = a->y - b->y;
		result->z = a->z - b->z;
	}
	else
	{
		result->x = a->x + b->x;
		result->y = a->y + b->y;
		result->z = a->z + b->z;
	}
}
