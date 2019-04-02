/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructive_geometry.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:36:45 by lwyl-the          #+#    #+#             */
/*   Updated: 2019/04/02 18:39:46 by lwyl-the         ###   ########.fr       */
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
	return (ft_dmax(-dist_a, dist_b));
}
