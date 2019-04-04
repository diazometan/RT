/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_tracing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 15:48:11 by lwyl-the          #+#    #+#             */
/*   Updated: 2019/04/04 20:02:20 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*double path_tracing(t_shape *shape, t_rt *rt, int depth)
{
	int rgb[3];
	int color;
	double r1;
	double r2;
	int i = 0;
	t_coord n_t;
	t_coord n_b;
	t_coord sample;
	t_coord sample_world;

	color = 0;
	rgb[0] = 0;
	rgb[1] = 0;
	rgb[2] = 0;
	if (depth == 0)
		return (0);
	create_coord_system(shape, &n_t, &n_b);
	double pdf = 1 / (2 * M_PI);
	while (i < 32)
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
			if (check_intersection(&sample_world, shape, rt, depth))
				closest = shape;
			shape = shape->next;
		}
		if (closest == NULL)
			;
		else
		{
			//get_normal(closest, rt, &sample_world, depth);
			//rt->source_point = &closest->surface_point;
			color = get_color(closest, rt, &sample_world, depth);
			rgb[0] += (color >> 16 & 0xFF) * r1;
			rgb[1] += (color >> 8 & 0xFF) * r1;
			rgb[2] += (color) * r1;
		}
		i++;
	}
	rgb[0] /= 32;
	rgb[1] /= 32;
	rgb[2] /= 32;
	color = ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
	return (color);
}*/

void create_coord_system(t_shape *shape, t_vec3 *n_t, t_vec3 *n_b)
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
		n_t->y = shape->normal.z;
		n_t->z = shape->normal.y;
	}
	vec3_normalize(n_t, vec3_length(n_t));
	vec3_cross(&shape->normal, n_t, n_b);
}

void init_ray_pt(double r1, double r2, t_vec3 *rand_dir)
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

void init_sample_world(t_shape *shape, t_vec3 n_b, t_vec3 n_t, t_vec3 sample, t_vec3 *sample_world)
{
	sample_world->x = sample.x * n_b.x + sample.y * shape->normal.x + sample.z * n_t.x;
	sample_world->y = sample.x * n_b.y + sample.y * shape->normal.y + sample.z * n_t.y;
	sample_world->z = sample.x * n_b.z + sample.y * shape->normal.z + sample.z * n_t.z;
}

t_shape				*trace_ray_emmision(t_vec3 *dir, t_rt *rt)
{
	double max_distance;
	double min_distance;
	double epsilon;
	double t;
	double d;
	t_shape *head;
	t_shape	*closest;

	max_distance = 100;
	epsilon = 10e-6;
	t = 0;
	closest = NULL;
	while (t < max_distance)
	{
		head = rt->head_shapes;
		min_distance = INT_MAX;
		t_vec3 from;
		from.x = rt->source_point->x + t * dir->x;
		from.y = rt->source_point->y + t * dir->y;
		from.z = rt->source_point->z + t * dir->z;
		while (head != NULL)
		{
			d = head->gd_fun(&from, head);
			if (d < min_distance)
			{
				min_distance = d;
				closest = head;
			}
			head = head->next;
		}
		if (min_distance <= epsilon * t)
		{
			rt->t_closest = t;
			return (closest);
		}
		t += min_distance;
	}
	return (NULL);
}

double			path_tracing(t_vec3 source, t_shape *shape, t_rt *rt, int depth)
{
	t_shape *hit;
	t_vec3	new_dir;
	double	emittance;
	double	cos_theta;
	double	incoming;
	t_matrix rotation;

	t_vec3 n_t;
	t_vec3 n_b;
	t_vec3 sample;
	double r1;
	double r2;

	r1 = drand48();
	r2 = drand48();

	if (depth < 0)
		return (0);

	rt->source_point = &source;
	create_coord_system(shape, &n_t, &n_b);
	init_ray_pt(r1, r2, &sample);
	init_sample_world(shape, n_b, n_t, sample, &new_dir);
	//vec3_subtract(&new_dir, &source, &new_dir);
	//vec3_normalize(&new_dir, vec3_length(&new_dir));
	if ((hit = trace_ray_emmision(&new_dir, rt)) == NULL)
		return (shape->emission);
	emittance = shape->emission;

	get_intersection_point(&source, &new_dir, rt->t_closest, &hit->surface_point);
	//printf("%f   %f   %f\n", new_dir.x, new_dir.y, new_dir.z);
	//new_dir = hit->normal;

	//printf("%f   %f   %f   ", new_dir.x, new_dir.y, new_dir.z);
	//rotation = matrix_multiply(x_rotation_matrix(M_PI / 6.0), y_rotation_matrix(M_PI / 6.0));
	//vector_matrix_multiply(rotation, &new_dir);
	//printf("%f   %f   %f\n", new_dir.x, new_dir.y, new_dir.z);
	cos_theta = vec3_dot(&new_dir, &hit->normal);
	incoming = path_tracing(hit->surface_point, shape, rt, depth - 1);
	return (emittance + ((1 / M_PI) * incoming * 1 / (1 / (2 * M_PI))));
}

double			emission(t_shape *shape, t_rt *rt, int depth)
{
	int i = 0;
	double	light = 0.0;
	double max;
	t_vec3 	dir;
	t_vec3	p;

	p = shape->surface_point;
	while (i < 1)
	{
		light += path_tracing(p, shape, rt, depth);
		i++;
	}
	light = light / (double)i;
	if (light > 1)
		light = 1.0;
	return (light);
}
