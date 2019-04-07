/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructive_geometry.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:36:45 by lwyl-the          #+#    #+#             */
/*   Updated: 2019/04/07 21:03:02 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double			intersect(t_vec3 *p, t_shape *shape1, t_shape *shape2)
{
	double dist_a;
	double dist_b;

	dist_a = shape_summ(p, shape1);
	dist_b = shape_summ(p, shape2);
	return (ft_dmax(dist_a, dist_b));
}

double			unite(t_vec3 *p, t_shape *shape1, t_shape *shape2)
{
	double dist_a;
	double dist_b;

	dist_a = shape_summ(p, shape1);
	dist_b = shape_summ(p, shape2);
	return (ft_dmin(dist_a, dist_b));
}

double			difference(t_vec3 *p, t_shape *shape1, t_shape *shape2)
{
	double dist_a;
	double dist_b;

	dist_a = shape_summ(p, shape1);
	dist_b = shape_summ(p, shape2);
	return (ft_dmax(-dist_a, dist_b));
}

double			cut(t_vec3 *p, t_shape *shape1, t_shape *shape2)
{


	double dist_a;
	double dist_b;
	t_vec3 orig;

	dist_a = shape_summ(p, shape1);
	if (shape2->figure != PLANE)
	{
		ft_putstr("shape2 mast be plane\n");
		exit(0);
	}
	vec3_subtract(p, &shape2->center, &orig);
	dist_b = vec3_dot(&shape2->unit, &orig);
	return (ft_dmax(dist_a, dist_b));
}

double			blend(double dist_a, double dist_b)
{
	//убрать константу
	double res;
	double k = 5;

	res = exp(-k * dist_a) + exp(-k * dist_b);
	return (-log(ft_dmax(0.0001f, res)) / k);
}

double			mix(double dist_a, double dist_b)
{
	//убрать константу
	double t = 0.5;
	return (dist_a * (1 - t) + dist_b * t);
}
