/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:10:02 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/19 14:57:29 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double		shadow(t_vec3 *orig, t_vec3 dir,
			t_shape *head_shape, double max_distance)
{
	t_trace	dist;
	t_vec3	from;
	t_shape	*head;

	dist.t = 0.0001;
	dist.epsilon = 10e-9;
	vec3_normalize(&dir, max_distance);
	while (dist.t < max_distance)
	{
		head = head_shape;
		dist.min_distance = INT_MAX;
		from.x = orig->x + dist.t * dir.x;
		from.y = orig->y + dist.t * dir.y;
		from.z = orig->z + dist.t * dir.z;
		while (head != NULL)
		{
			if (head->child == 0)
			{
				dist.d = shape_summ(&from, head);
				if (dist.d < dist.min_distance)
					dist.min_distance = dist.d;
				if (dist.min_distance <= dist.t * dist.epsilon)
				{
					if (head->transparency)
						return (head->transparency);
					return (0.0);
				}
			}
			head = head->next;
		}
		dist.t += dist.min_distance;
	}
	return (1.0);
}
