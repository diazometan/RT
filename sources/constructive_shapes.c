/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructive_shapes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 17:31:45 by lwyl-the          #+#    #+#             */
/*   Updated: 2019/04/05 19:55:05 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	shape_one(t_vec3 *p, t_shape *shape)
{
	double sphere;
	double box;

	sphere = gd_sphere(p, shape);
	box = gd_box(p, shape);
	return (difference(box, sphere));
}

