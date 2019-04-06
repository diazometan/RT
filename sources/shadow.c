/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:10:02 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/06 19:10:24 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				shadow(t_vec3 *orig, t_vec3 dir, t_shape *head_shape, double max_distance)
{
	double min_distance;
	double epsilon;
	double t;
	double d;
	t_vec3 from;
	t_shape *head;

	t = 0.0;
	epsilon = 10e-5;
	vec3_normalize(&dir, max_distance);
	while (t < max_distance)
	{
		head = head_shape;
		min_distance = INT_MAX;
		from.x = orig->x + t * dir.x;
		from.y = orig->y + t * dir.y;
		from.z = orig->z + t * dir.z;
		while (head != NULL)
		{
			if (head->f_is_in_group == 0)
			{
				// d = head->gd_fun(&from, head);
				d = shape_summ(&from, head);
				if (d < min_distance)
					min_distance = d;
				if (min_distance <= t * epsilon)
					return (1);
			}
			head = head->next;
		}
		t += min_distance;
	}
	return (0);
}
