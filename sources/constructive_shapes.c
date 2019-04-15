/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructive_shapes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 17:31:45 by lwyl-the          #+#    #+#             */
/*   Updated: 2019/04/15 13:39:14 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	ft_dmod(double a, double b) //добавить в либу
{
	return (a - b * floor(a/b));
}

double	fractal(t_vec3 *p, t_shape *shape) //добавить степень фрактала
{
	double d;
	double c;
	double s;
	int i;

	t_vec3 a;
	t_vec3 r;
	t_vec3 tmp;

	vec3_subtract(p, &shape->center, &tmp);
	vector_matrix_multiply(shape->rotation, &tmp);

	i = 0;
	s = 1.0;

	d = gd_box(p, shape);
	while (i < 4)
	{
		a.x = ft_dmod(tmp.x * s, 2.0) - 1.0;
		a.y = ft_dmod(tmp.y * s, 2.0) - 1.0;
		a.z = ft_dmod(tmp.z * s, 2.0) - 1.0;
		s *= 3.0;
		r.x = fabs(1.0 - 3.0 * fabs(a.x));
		r.y = fabs(1.0 - 3.0 * fabs(a.y));
		r.z = fabs(1.0 - 3.0 * fabs(a.z));

		float da = ft_dmax(r.x, r.y);
		float db = ft_dmax(r.y, r.z);
		float dc = ft_dmax(r.z, r.x);
		c = (ft_dmin(da, ft_dmin(db, dc)) - 1.0) / s;
		d = difference(-c, d);
		i++;
	}
	return (d);
}
