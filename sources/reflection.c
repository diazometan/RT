/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 17:40:19 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/18 18:02:52 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	reflect_ray(t_shape *shape, t_coord *r_v, t_coord *dir)
{
	double	n_dot_r;

	scalar_product(dir, (-1));
	n_dot_r = dot_product(&shape->normal, dir);
	r_v->x = 2 * shape->normal.x * n_dot_r - dir->x;
	r_v->y = 2 * shape->normal.y * n_dot_r - dir->y;
	r_v->z = 2 * shape->normal.z * n_dot_r - dir->z;
}

int		reflection(t_coord *dir, t_shape *shape, t_rt *rt, int depth)
{
	int	reflected_color;
	t_coord r_v;

	reflect_ray(shape, &r_v, dir);
	rt->source_point = &shape->surface_point;
	reflected_color = trace_ray(&r_v, rt, depth - 1);
	return (reflected_color);
}
