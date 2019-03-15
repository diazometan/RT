/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_shadow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 21:12:14 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/15 11:21:26 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	init_ray_shadow(t_ray *ray, t_light *light,
					t_shape *source_shape, t_shape *shape)
{
	coord_add_subtract(&source_shape->surface_point,
							&shape->center, &ray->a, 1);
	ray->min = 0.0001;
	if (light->type == 1)
	{
		ray->max = 1.0;
		coord_add_subtract(&light->point,
				&source_shape->surface_point, &ray->b, 1);
	}
	else
	{
		ray->max = INT_MAX;
		ray->b.x = light->point.x;
		ray->b.y = light->point.y;
		ray->b.z = light->point.z;
	}
}

int			check_shadow(t_shape *source_shape, t_light *light, t_rt *rt)
{
	t_ray	ray;
	t_shape	*head;

	head = rt->head_shapes;
	while (head != NULL)
	{
		if (head != source_shape)
		{
			init_ray_shadow(&ray, light, source_shape, head);
			if (head->figure == PLANE &&
				(plane_intersection(head, &ray, rt)) != INT_MAX)
				return (0);
			else if (head->figure == SPHERE &&
				(sphere_intersection(head, &ray)) != INT_MAX)
				return (0);
			else if (head->figure == CYLINDER &&
				(cylinder_intersection(head, &ray, rt)) != INT_MAX)
				return (0);
			else if (head->figure == CONE &&
				(cone_intersection(head, &ray, rt)) != INT_MAX)
				return (0);
		}
		head = head->next;
	}
	return (1);
}
