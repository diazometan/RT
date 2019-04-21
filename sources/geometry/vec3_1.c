/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 10:40:53 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/21 18:26:08 by lwyl-the         ###   ########.fr       */
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
