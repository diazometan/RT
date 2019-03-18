/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_caps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 11:10:19 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/18 17:39:51 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		init_cone_cap(t_shape *cone, t_rt *rt)
{
	t_shape	*cap;

	cap = (t_shape *)malloc(sizeof(t_shape));
	cap->figure = DISK;
	cap->color = cone->color;
	cap->specular = cone->specular;
	cap->reflection = cone->reflection;
	cap->next = NULL;
	cap->center = (t_coord) {cone->center.x + cone->h * cone->unit.x,
							cone->center.y + cone->h * cone->unit.y,
							cone->center.z + cone->h * cone->unit.z};
	cap->unit = (t_coord) {cone->unit.x, cone->unit.y, cone->unit.z};
	cap->radius = cone->h * tan(cone->angle);
	push_back_shape(&rt->head_shapes, cap);
}

static void		init_cylinder_caps(t_shape *cylinder, t_rt *rt, int flag)
{
	t_shape	*cap;

	cap = (t_shape *)malloc(sizeof(t_shape));
	cap->figure = DISK;
	cap->color = cylinder->color;
	cap->specular = cylinder->specular;
	cap->reflection = cylinder->reflection;
	if (flag)
		cap->center = (t_coord) {cylinder->center.x + cylinder->h *
				cylinder->unit.x, cylinder->center.y + cylinder->h *
				cylinder->unit.y, cylinder->center.z + cylinder->h *
													cylinder->unit.z};
	else
		cap->center = (t_coord) {cylinder->center.x,
				cylinder->center.y, cylinder->center.z};
	cap->radius = cylinder->radius;
	cap->unit = (t_coord) {cylinder->unit.x,
			cylinder->unit.y, cylinder->unit.z};
	cap->next = NULL;
	push_back_shape(&rt->head_shapes, cap);
}

void			create_caps(t_rt *rt)
{
	t_shape *shape;

	shape = rt->head_shapes;
	while (shape)
	{
		if (shape->figure == CYLINDER)
		{
			init_cylinder_caps(shape, rt, 0);
			init_cylinder_caps(shape, rt, 1);
		}
		else if (shape->figure == CONE)
			init_cone_cap(shape, rt);
		shape = shape->next;
	}
}
