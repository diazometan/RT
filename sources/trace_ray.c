/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 19:36:59 by lwyl-the          #+#    #+#             */
/*   Updated: 2019/04/21 12:20:54 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_shape			*calculation_distance(t_trace *dist, t_rt *rt, t_vec3 *dir)
{
	t_shape		*head;
	t_shape		*closest;
	t_vec3		from;

	head = rt->head_shapes;
	dist->min_distance = INT_MAX;
	closest = NULL;
	get_intersection_point(&rt->source_point, dir, dist->t, &from);
	while (head != NULL)
	{
		if (head->child == 0)
		{
			dist->d = fabs(shape_summ(&from, head));
			if (dist->d < dist->min_distance)
			{
				dist->min_distance = dist->d;
				closest = head;
			}
		}
		head = head->next;
	}
	return (closest);
}

int				trace_ray(t_vec3 *dir, t_rt *rt, int depth)
{
	t_trace		dist;
	t_shape		*closest;

	dist.max_distance = 100;
	dist.epsilon = 10e-9;
	dist.t = 0.0001;
	while (dist.t < dist.max_distance)
	{
		closest = calculation_distance(&dist, rt, dir);
		if (dist.min_distance <= dist.epsilon * dist.t && closest != NULL)
		{
			rt->t_closest = dist.t;
			return (get_color(dir, closest, rt, depth));
		}
		dist.t += dist.min_distance;
	}
	return (0);
}
