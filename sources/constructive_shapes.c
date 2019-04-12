/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructive_shapes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 17:31:45 by lwyl-the          #+#    #+#             */
/*   Updated: 2019/04/11 21:21:05 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*double			gd_box_two(double x, double y, double z, t_shape *shape, t_vec3 dim)
{
	t_vec3 d;
	t_vec3 orig;
	t_vec3 len;

	d.x = fabs(x) - dim.x;
	d.y = fabs(y) - dim.y;
	d.z = fabs(z) - dim.z;
	len.x = ft_dmax(d.x, 0.0);
	len.y = ft_dmax(d.y, 0.0);
	len.z = ft_dmax(d.z, 0.0);
	return (vec3_length(&len) - 0 + ft_dmin(ft_dmax(d.x, ft_dmax(d.y, d.z)), 0.0));
}

double	cross(t_vec3 *p, t_shape *shape)
{
	double box1;
	double box2;
	double box3;

	t_vec3 dim1;
	t_vec3 dim2;
	t_vec3 dim3;
	t_vec3 tmp;

	dim1 = (t_vec3) {INFINITY, 1.0, 1.0};
	dim2 = (t_vec3) {1.0, INFINITY, 1.0};
	dim3 = (t_vec3) {1.0, 1.0, INFINITY};

	tmp = (t_vec3) {p->x, p->y, p->z};
	box1 = gd_box_two(tmp.x, tmp.y, tmp.z, shape, dim1);
	box2 = gd_box_two(tmp.y, tmp.z, tmp.x, shape, dim2);
	box3 = gd_box_two(tmp.z, tmp.x, tmp.y, shape, dim3);
	return (unite(box1, unite(box2, box3)));
}*/

double	ft_dmod(double a, double b)
{
	return (a - b * floor(a/b));
}

double	fractal(t_vec3 *p, t_shape *shape)
{
	double d;
	double c;
	double s;
	int i;
	//t_vec3 dim;
	t_vec3 a;
	t_vec3 r;
	t_vec3 tmp;

	vec3_subtract(p, &shape->center, &tmp);
	vector_matrix_multiply(shape->rotation, &tmp);

	i = 0;
	s = 1.0;

	//dim = (t_vec3) {shape->dims.x, shape->dims.y, shape->dims.z};
	d = gd_box(p, shape);//gd_box_two(tmp.x, tmp.y, tmp.z, shape, dim);
	while (i < 4)
	{
		a.x = ft_dmod(tmp.x * s, 2.0) - 1.0;
		a.y = ft_dmod(tmp.y * s, 2.0) - 1.0;
		a.z = ft_dmod(tmp.z * s, 2.0) - 1.0;
		s *= 3.0;
		r.x = fabs(1.0 - 3.0 * fabs(a.x));
		r.y = fabs(1.0 - 3.0 * fabs(a.y));
		r.z = fabs(1.0 - 3.0 * fabs(a.z));

		//c = cross(&r, shape) / s;
		float da = ft_dmax(r.x, r.y);
		float db = ft_dmax(r.y, r.z);
		float dc = ft_dmax(r.z, r.x);
		c = (ft_dmin(da, ft_dmin(db, dc)) - 1.0) / s;
		d = difference(-c, d);
		i++;
	}
	return (d);
}
