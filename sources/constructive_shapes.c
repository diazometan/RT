/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructive_shapes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 17:31:45 by lwyl-the          #+#    #+#             */
/*   Updated: 2019/04/08 14:01:06 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	shape_summ(t_vec3 *p, t_shape *shape)
{
	double dist_a;
	double dist_b;

	if(!shape->f_is_group)
		return (shape->gd_fun(p, shape));
	else
	{
		dist_a = shape_summ(p, shape->shape1);
		dist_b = shape_summ(p, shape->shape2);
		return (shape->gd_fun(dist_a, dist_b));
	}
}