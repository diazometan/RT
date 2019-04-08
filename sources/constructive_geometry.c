/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructive_geometry.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:36:45 by lwyl-the          #+#    #+#             */
/*   Updated: 2019/04/08 14:05:32 by rrhaenys         ###   ########.fr       */
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
