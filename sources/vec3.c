/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 10:40:53 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/13 14:56:08 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	vec3_add(t_vec3 *a, t_vec3 *b, t_vec3 *result)
{
	result->x = a->x + b->x;
	result->y = a->y + b->y;
	result->z = a->z + b->z;
}

void	vec3_subtract(t_vec3 *a, t_vec3 *b, t_vec3 *result)
{
	result->x = a->x - b->x;
	result->y = a->y - b->y;
	result->z = a->z - b->z;
}

void	vec3_scalar(t_vec3 *a, double number)
{
	a->x *= number;
	a->y *= number;
	a->z *= number;
}

double	vec3_dot(t_vec3 *a, t_vec3 *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

void	vec3_cross(t_vec3 *a, t_vec3 *b, t_vec3 *c)
{
	c->x = a->y * b->z - a->z * b->y;
	c->y = a->z * b->x - a->x * b->z;
	c->z = a->x * b->y - a->y * b->x;
}

double	vec3_length(t_vec3 *vector)
{
	return (sqrt(pow(vector->x, 2) + pow(vector->y, 2) + pow(vector->z, 2)));
}

void	vec3_normalize(t_vec3 *vector, double length)
{
	vector->x /= length;
	vector->y /= length;
	vector->z /= length;
}

void	get_intersection_point(t_vec3 *source, t_vec3 *ray, double t, t_vec3 *p)
{
	p->x = source->x + t * ray->x;
	p->y = source->y + t * ray->y;
	p->z = source->z + t * ray->z;
}
