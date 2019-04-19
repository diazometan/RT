/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transperency.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 18:55:18 by lwyl-the          #+#    #+#             */
/*   Updated: 2019/04/19 12:32:23 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			trans_color(int color, int trans_color, double transperency)
{
	int		rgb_ref[3];

	rgb_ref[0] = ((color >> 16) & 0xFF) * (1.0 - transperency) +
					((trans_color >> 16) & 0xFF) * transperency;
	rgb_ref[1] = ((color >> 8) & 0xFF) * (1.0 - transperency) +
					((trans_color >> 8) & 0xFF) * transperency;
	rgb_ref[2] = (color & 0xFF) * (1.0 - transperency) +
					(trans_color & 0xFF) * transperency;

	return ((rgb_ref[0] << 16) | (rgb_ref[1] << 8) | rgb_ref[2]);
}

static void	transperency_ray(t_vec3 *dir, t_shape *shape, t_vec3 *ref_r)
{
	int		flag;
	double	eta;
	double	k;
	double	cos_alpha;
	double	coef_a;

	flag = 1;
	cos_alpha = vec3_dot(dir, &shape->normal);
	cos_alpha = (-1.0) * (cos_alpha < 1.0 ? cos_alpha : 1.0);
	if (cos_alpha < 0)
	{
		cos_alpha *= (-1.0);
		flag = -1;
		eta = shape->refraction / 1.0;
	}
	else
		eta = 1.0 / shape->refraction;
	if ((k = 1.0 - eta * eta * (1.0 - cos_alpha * cos_alpha)) < 0)
		return ;
	coef_a = eta * cos_alpha - sqrt(k);
	ref_r->x = dir->x * eta + flag * shape->normal.x * coef_a;
	ref_r->y = dir->y * eta + flag * shape->normal.y * coef_a;
	ref_r->z = dir->z * eta + flag * shape->normal.z * coef_a;
}


int			transperency(t_vec3 *dir, t_shape *shape, t_rt *rt, int depth)
{
	int		trans_color;
	t_vec3	trans_r;

	trans_r = (t_vec3) {0, 0, 0};
	transperency_ray(dir, shape, &trans_r);
	rt->source_point = &shape->surface_point;
	vec3_normalize(&trans_r, vec3_length(&trans_r));
	trans_color = trace_ray(&trans_r, rt, depth);
	return (trans_color);
}
