/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:10:02 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/02 15:13:00 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				shadow(t_vec3 *orig, t_vec3 *dir, t_rt *rt, double max_distance)
{
	double min_distance;
	double epsilon;
	double t;
	double d;
	t_vec3 from;
	t_shape *head;

	t = 0.0;
	epsilon = 10e-5;
	while (t < max_distance)
	{
		head = rt->head_shapes;
		min_distance = INT_MAX;
		from.x = orig->x + t * dir->x;
		from.y = orig->y + t * dir->y;
		from.z = orig->z + t * dir->z;
		while (head != NULL)
		{
			d = gd_cone(&from, head);
			if (d < min_distance)
				min_distance = d;
			if (min_distance <= t * epsilon)
				return (0);
			head = head->next;
		}
		t += min_distance;
	}
	return (1);
}
