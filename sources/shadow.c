/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:10:02 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/12 14:57:27 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double				shadow(t_vec3 *orig, t_vec3 dir, t_shape *head_shape, double max_distance)
{
	double min_distance;
	double epsilon;
	double t;
	double d;
	t_vec3 from;
	t_shape *head;

	/*double res = 1.0;
	double ph = 1e20;
	double y;
	double x;
	double k = 2.0;*/

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
			d = head->gd_fun(&from, head);
			if (d < min_distance)
				min_distance = d;
			if (min_distance <= t * epsilon)
				return (0);
			head = head->next;
		}
		//y = d * d / (2.0 * ph);
		//x = sqrt(d * d - y * y);
		//res = ft_dmin(res, (2.0 * x) / (ft_dmax(0.0, t - y)));
		//res = ft_dmin(res, k * d / t);
		//ph = d;
		t += min_distance;
	}
	return (1.0);
}
