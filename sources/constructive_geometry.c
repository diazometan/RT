/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructive_geometry.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:36:45 by lwyl-the          #+#    #+#             */
/*   Updated: 2019/04/18 13:06:50 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double			intersect(double dist_a, double dist_b)
{
	return (ft_dmax(dist_a, dist_b));
}

double			unite(double dist_a, double dist_b)
{
	return (ft_dmin(dist_a, dist_b));
}

double			difference(double dist_a, double dist_b)
{
	return (ft_dmax(dist_a, -dist_b));
}

double			blend(double dist_a, double dist_b)
{
	double		res;
	double		k;

	k = 5.0;
	res = exp(-k * dist_a) + exp(-k * dist_b);
	return (-log(ft_dmax(0.0001f, res)) / k);
}

double			mix(double dist_a, double dist_b)
{
	double		t;

	t = 0.5;
	return (dist_a * (1 - t) + dist_b * t);
}
