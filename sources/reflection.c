/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 17:40:19 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/21 14:01:12 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			reflect_color(int color, int reflected_color, double reflection)
{
	int		rgb_ref[3];

	rgb_ref[0] = (color >> 16 & 0xFF) * (1.0 - reflection) +
					(reflected_color >> 16 & 0xFF) * reflection;
	rgb_ref[1] = (color >> 8 & 0xFF) * (1.0 - reflection) +
					(reflected_color >> 8 & 0xFF) * reflection;
	rgb_ref[2] = (color & 0xFF) * (1.0 - reflection) +
					(reflected_color & 0xFF) * reflection;
	return ((rgb_ref[0] << 16) | (rgb_ref[1] << 8) | rgb_ref[2]);
}

int			reflection(t_vec3 *dir, t_shape *shape, t_rt *rt, int depth)
{
	double	n_dot_r;
	t_vec3	r_v;

	vec3_scalar(dir, (-1.0));
	n_dot_r = vec3_dot(&rt->normal, dir);
	r_v.x = 2 * rt->normal.x * n_dot_r - dir->x;
	r_v.y = 2 * rt->normal.y * n_dot_r - dir->y;
	r_v.z = 2 * rt->normal.z * n_dot_r - dir->z;
	//rt->source_point = &shape->surface_point;
	return (trace_ray(&r_v, rt, depth));
}
