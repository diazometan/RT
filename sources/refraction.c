/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 10:19:27 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/20 11:36:10 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	swap_double(double *a, double *b)
{
	double tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void	refract_ray(t_coord *dir, t_shape *shape, t_coord *ref_r)
{
	int		flag;
	double	eta;
	double	k;
	double	cos_alpha;
	double	coef_a;

	flag = 1;
	cos_alpha = dot_product(dir, &shape->normal);
	cos_alpha = (-1) * (cos_alpha < 1.0 ? cos_alpha : 1.0);
	if (cos_alpha < 0)
	{
		cos_alpha *= (-1);
		flag = -1;
		eta = shape->refract / 1.0;
	}
	else
		eta = 1.0 / shape->refract;
	if ((k = 1 - eta * eta * (1 - cos_alpha * cos_alpha)) < 0)
		return ;
	coef_a = eta * cos_alpha - sqrt(k);
	ref_r->x = dir->x * eta + flag * shape->normal.x * coef_a;
	ref_r->y = dir->y * eta + flag * shape->normal.y * coef_a;
	ref_r->z = dir->z * eta + flag * shape->normal.z * coef_a;
}

int refraction(t_coord *dir, t_shape *shape, t_rt *rt, int depth)
{
	int	trans_color;
	t_coord ref_r;

	ref_r = (t_coord) {1, 0, 0};
	refract_ray(dir, shape, &ref_r);
	rt->source_point = &shape->surface_point;
	trans_color = trace_ray(&ref_r, rt, depth);
	return (trans_color);
}
