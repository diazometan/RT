/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 10:19:27 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/20 10:25:24 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_swap_new(double *a, double *b)
{
	double tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

double	ft_smallest(double a, double b)
{
	if (b < a)
		return (b);
	return (a);
}

double	ft_biggest(double a, double b)
{
	if (b > a)
		return (b);
	return (a);
}

void	refract_ray(t_coord *dir, t_shape *shape, t_coord *ref_r)
{
	double n_dot_d;
	double eta;
	double etai;
	double etat;
	double k;
	double cosi;
	t_coord normal;

	ref_r->x = 1;
	ref_r->y = 0;
	ref_r->z = 0;
	etai = 1.0;
	etat = shape->refract;
	normal.x = shape->normal.x;
	normal.y = shape->normal.y;
	normal.z = shape->normal.z;
	n_dot_d = dot_product(dir, &normal);
	cosi = (-1.0) * ft_biggest(-1.0, ft_smallest(1.0, n_dot_d));
	if (cosi < 0)
	{
		cosi *= (-1);
		scalar_product(&normal, -1.0);
		ft_swap_new(&etai, &etat);
	}
	eta = etai / etat;
	k = 1 - eta * eta * (1 - cosi * cosi);
	if (k < 0)
		;
	ref_r->x = dir->x * eta + normal.x * (eta * cosi - sqrt(k));
	ref_r->y = dir->y * eta + normal.y * (eta * cosi - sqrt(k));
	ref_r->z = dir->z * eta + normal.z * (eta * cosi - sqrt(k));
}

int refraction(t_coord *dir, t_shape *shape, t_rt *rt, int depth)
{
	int	trans_color;
	t_coord ref_r;

	refract_ray(dir, shape, &ref_r);
	rt->source_point = &shape->surface_point;
	trans_color = trace_ray(&ref_r, rt, depth);
	return (trans_color);
}
