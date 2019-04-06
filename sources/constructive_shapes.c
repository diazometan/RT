/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructive_shapes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 17:31:45 by lwyl-the          #+#    #+#             */
/*   Updated: 2019/04/06 17:57:20 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	shape_one(t_vec3 *p, t_shape *shape)
{
	double sphere;
	double box;

	sphere = shape->gd_fun(p, shape);
	box = gd_box(p, shape);
	return (difference(box, sphere));
}

double	shape_summ(t_vec3 *p, t_shape *shape)
{
	double shape1;
	double shape2;

	if(shape->shape2 == NULL)
		return (shape->gd_fun(p, shape));
	else
	{
		shape1 = shape_summ(p, shape->shape1);
		shape2 = shape_summ(p, shape->shape2);
		return (shape->constructive_fun(shape1, shape2));
	}
}