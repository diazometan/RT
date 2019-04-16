/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 17:40:19 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/16 19:14:25 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			reflection(t_vec3 *dir, t_shape *shape, t_rt *rt, int depth)
{
	double	n_dot_r;
	t_vec3	r_v;

	vec3_scalar(dir, (-1.0));
	n_dot_r = vec3_dot(&shape->normal, dir);
	r_v.x = 2 * shape->normal.x * n_dot_r - dir->x;
	r_v.y = 2 * shape->normal.y * n_dot_r - dir->y;
	r_v.z = 2 * shape->normal.z * n_dot_r - dir->z;
	rt->source_point = &shape->surface_point;
	return (trace_ray(&r_v, rt, depth));
}
