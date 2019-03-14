/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 16:38:12 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/14 20:13:01 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	cut_triangle(t_coord *p, t_shape *shape)
{
	t_coord	a;
	t_coord	b;
	t_coord	c;
	t_coord	v1;
	t_coord	v2;
	t_coord	v3;
	t_coord	f1;
	t_coord	f2;
	t_coord	f3;
	double check1;
	double check2;
	double check3;

	coord_add_subtract(&shape->triangle[2], &shape->triangle[0], &a, 1);
	coord_add_subtract(&shape->triangle[1], &shape->triangle[2], &b, 1);
	//printf("x1 - %f y2 - %f z3 - %f\n", b.x, b.y, b.z);
	coord_add_subtract(&shape->triangle[0], &shape->triangle[1], &c, 1);

	coord_add_subtract(p, &shape->triangle[0], &v1, 1);
	coord_add_subtract(p, &shape->triangle[2], &v2, 1);
	//printf("x1 - %f y2 - %f z3 - %f\n", v2.x, v2.y, v2.z);
	coord_add_subtract(p, &shape->triangle[1], &v3, 1);

	cross_product(&v1, &a, &f1);
	cross_product(&v2, &b, &f2);
	//printf("cros - x - %f y - %f z - %f\n", f2.x, f2.y, f2.z);
	cross_product(&v3, &c, &f3);
	check1 = dot_product(&f1, &shape->unit);
	check2 = dot_product(&f2, &shape->unit);
	//printf("check2 - %f\n", check2);
	check3 = dot_product(&f3, &shape->unit);
	//printf("u1 - %f u2 - %f u3 - %f\n", shape->unit.x, shape->unit.y, shape->unit.z);
	//printf("1 - %f 2 - %f 3 - %f\n", check1, check2, check3);
	if (check1 >= 0 && check2 >= 0 && check3 >= 0)
		return (1);
	return (0);
}

double			triangle_intersection(t_shape *shape, t_ray *ray, t_rt *rt)
{
	double	intersection;
	t_coord	a;
	t_coord	b;
	t_coord	p;

	a.x = shape->triangle[1].x - shape->triangle[0].x;
	a.y = shape->triangle[1].y - shape->triangle[0].y;
	a.z = shape->triangle[1].z - shape->triangle[0].z;

	b.x = shape->triangle[2].x - shape->triangle[0].x;
	b.y = shape->triangle[2].y - shape->triangle[0].y;
	b.z = shape->triangle[2].z - shape->triangle[0].z;

	ray->a.x = (shape->triangle[0].x + shape->triangle[1].x + shape->triangle[2].x) / 3;
	ray->a.y = (shape->triangle[0].y + shape->triangle[1].y + shape->triangle[2].y) / 3;
	ray->a.z = (shape->triangle[0].z + shape->triangle[1].z + shape->triangle[2].z) / 3;
	//printf("center x - %f y - %f z - %f\n", ray->a.x, ray->a.y, ray->a.z);
	coord_add_subtract(&rt->camera, &ray->a, &ray->a, 1);
	cross_product(&a, &b, &shape->unit);

	intersection =  plane_intersection(shape, ray);

	p.x = rt->camera.x + intersection * shape->ray.x;
	p.y = rt->camera.y + intersection * shape->ray.y;
	p.z = rt->camera.z + intersection * shape->ray.z;
	//printf("x - %f y - %f z - %f\n", p.x, p.y, p.z);

	if (intersection != INT_MAX && cut_triangle(&p, shape))
		return (intersection);
	return (INT_MAX);
	//return (intersection);
}
