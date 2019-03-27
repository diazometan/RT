/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_tracing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 15:48:11 by lwyl-the          #+#    #+#             */
/*   Updated: 2019/03/27 17:36:32 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void create_coord_system(t_shape *shape, t_coord *n_t, t_coord *n_b)
{
	if (fabs(shape->normal.x) > fabs(shape->normal.y))
	{
		n_t->x = -shape->normal.z;
		n_t->y = 0;
		n_t->z = -shape->normal.x;
	}
	else
	{
		n_t->x = 0;
		n_t->y = -shape->normal.z;
		n_t->z = shape->normal.y;
	}
	normalize_vector(n_t, vector_length(n_t));
	cross_product(&shape->normal, n_t, n_b);
}

void init_ray_pt(double r1, double r2, t_coord *rand_dir)
{
	double sin_theta;
	double phi;
	double x;
	double z;

	sin_theta = sqrt(1 - r1 * r1);
	phi = 2 * M_PI * r2;
	x = sin_theta * cos(phi);
	z = sin_theta * sin(phi);
	rand_dir->x = x;
	rand_dir->y = r1;
	rand_dir->z = z;
}

void init_sample_world(t_shape *shape, t_coord n_b, t_coord n_t, t_coord sample, t_coord *sample_world)
{
	sample_world->x = sample.x * n_b.x + sample.y * shape->normal.x + sample.z * n_t.x;
	sample_world->y = sample.x * n_b.y + sample.y * shape->normal.y + sample.z * n_t.y;
	sample_world->z = sample.x * n_b.z + sample.y * shape->normal.z + sample.z * n_t.z;
}


double path_tracing(t_shape *shape, t_rt *rt, int depth)
{
	double light;
	double cur_light;
	double r1;
	double r2;
	int i = 0;
	t_coord n_t;
	t_coord n_b;
	t_coord sample;
	t_coord sample_world;

	light = 0.0;
	if (depth == 0)
		return (0);
	create_coord_system(shape, &n_t, &n_b);
	double pdf = 1 / (2 * M_PI);
	while (i < 16)
	{
		r1 = drand48();
		r2 = drand48();
		init_ray_pt(r1, r2, &sample);
		init_sample_world(shape, n_b, n_t, sample, &sample_world);
		t_shape	*closest;
		t_shape	*shape;

		shape = rt->head_shapes;
		closest = NULL;
		rt->t_closest = INT_MAX;
		while (shape != NULL)
		{
			if (check_intersection(&sample_world, shape, rt, depth - 1))
				closest = shape;
			shape = shape->next;
		}
		if (closest == NULL)
			cur_light = 0;
		else
			cur_light = get_light(shape, rt, &sample_world);
		light += r1 * cur_light / pdf;
	}
	light /= 16.0;
	return (light);
}
