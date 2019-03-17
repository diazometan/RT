/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_shadow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 21:12:14 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/17 13:44:03 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	init_ray_shadow(t_vectors *vectors, t_light *light,
								t_shape *source, t_shape *shape)
{
	coord_add_subtract(&source->surface_point,
				&shape->center, &vectors->orig, 1);
	vectors->min = 0.0001;
	if (light->type == POINT)
	{
		vectors->max = 1.0;
		coord_add_subtract(&light->point,
				&source->surface_point, vectors->dir, 1);
	}
	else
	{
		vectors->max = INT_MAX;
		vectors->dir->x = light->ray.x;
		vectors->dir->y = light->ray.y;
		vectors->dir->z = light->ray.z;
	}
}

int			check_shadow(t_shape *source_shape, t_light *light, t_rt *rt)
{
	t_coord		dir;
	t_vectors	vectors;
	t_shape	*head;

	head = rt->head_shapes;
	vectors.dir = &dir;
	while (head != NULL)
	{
		if (head != source_shape)
		{
			init_ray_shadow(&vectors, light, source_shape, head);
			if (head->figure == PLANE &&
				(plane_intersection(head, &vectors, rt)) != INT_MAX)
				return (0);
			else if (head->figure == SPHERE &&
				(sphere_intersection(head, &vectors)) != INT_MAX)
				return (0);
			else if (head->figure == CYLINDER &&
				(cylinder_intersection(head, &vectors, rt)) != INT_MAX)
				return (0);
			else if (head->figure == CONE &&
				(cone_intersection(head, &vectors, rt)) != INT_MAX)
				return (0);
		}
		head = head->next;
	}
	return (1);
}
