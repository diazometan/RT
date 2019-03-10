/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 16:38:45 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/05 18:35:12 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	dot_product(t_coord *a, t_coord *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
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
