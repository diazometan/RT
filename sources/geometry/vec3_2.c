/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 18:24:40 by lwyl-the          #+#    #+#             */
/*   Updated: 2019/04/21 18:26:06 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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

void	get_intersection_point(t_vec3 *source, t_vec3 *ray, double t, t_vec3 *p)
{
	p->x = source->x + t * ray->x;
	p->y = source->y + t * ray->y;
	p->z = source->z + t * ray->z;
}
