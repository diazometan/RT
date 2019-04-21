/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_summ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:30:34 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/04/17 21:14:49 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	shape_summ(t_vec3 *p, t_shape *shape)
{
	double dist_a;
	double dist_b;

	if (shape->group)
	{
		dist_a = shape_summ(p, shape->child_one);
		dist_b = shape_summ(p, shape->child_two);
		return (shape->gd_fun(dist_a, dist_b));
	}
	else
		return (shape->gd_fun(p, shape));
}
