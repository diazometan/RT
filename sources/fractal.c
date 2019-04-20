/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 17:31:45 by lwyl-the          #+#    #+#             */
/*   Updated: 2019/04/20 14:25:59 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double	create_side(t_vec3 tmp, double *s)
{
	double		da;
	double		db;
	double		dc;
	t_vec3		a;
	t_vec3		r;

	a.x = ft_dmod(tmp.x * (*s), 2.0) - 1.0;
	a.y = ft_dmod(tmp.y * (*s), 2.0) - 1.0;
	a.z = ft_dmod(tmp.z * (*s), 2.0) - 1.0;
	*s *= 3.0;
	r.x = fabs(1.0 - 3.0 * fabs(a.x));
	r.y = fabs(1.0 - 3.0 * fabs(a.y));
	r.z = fabs(1.0 - 3.0 * fabs(a.z));
	da = ft_dmax(r.x, r.y);
	db = ft_dmax(r.y, r.z);
	dc = ft_dmax(r.z, r.x);
	return (ft_dmin(da, ft_dmin(db, dc)) - 1.0);
}

double			gd_fractal(t_vec3 *p, t_shape *shape)
{
	t_vec3		tmp;
	double		s;
	double		d;
	double		c;
	int			i;

	i = 0;
	s = 1.0;
	vec3_subtract(p, &shape->center, &tmp);
	vector_matrix_multiply(shape->rotation, &tmp);
	d = gd_box(p, shape);
	while (i < 4)
	{
		c = create_side(tmp, &s) / s;
		d = difference(d, -c);
		i++;
	}
	return (d);
}
