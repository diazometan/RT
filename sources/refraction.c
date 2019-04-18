/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 10:19:27 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/18 19:25:05 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	refract_ray(t_vec3 *dir, t_shape *shape, t_vec3 *ref_r)
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


int			refraction(t_vec3 *dir, t_shape *shape, t_rt *rt, int depth)
{
	int		refract_color;
	t_vec3	ref_r;

	ref_r = (t_vec3) {0, 0, 0};
	refract_ray(dir, shape, &ref_r);
	rt->source_point = &shape->surface_point;
	vec3_normalize(&ref_r, vec3_length(&ref_r));
	refract_color = trace_ray(&ref_r, rt, depth);
	return (refract_color);
}
