/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:29:21 by lwyl-the          #+#    #+#             */
/*   Updated: 2019/03/19 17:07:06 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	check_color(int rgb[3])
{
	int	i;
	int	j;
	int	f;
	int	tmp;

	f = 1;
	while (f)
	{
		i = -1;
		f = 0;
		while (++i < 3)
			if (rgb[i] > 255)
			{
				f = 1;
				tmp = rgb[i] - 255;
				rgb[i] = 255;
				j = -1;
				while (++j < 3)
					if (j != i)
						rgb[j] += tmp / 2;
				break ;
			}
	}
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

int		reflect_color(int color, int reflected_color, t_shape *shape)
{
	int		rgb_ref[3];

	rgb_ref[0] = (color >> 16 & 0xFF) * (1 - shape->reflection) +
					(reflected_color >> 16 & 0xFF) * shape->reflection;
	rgb_ref[1] = (color >> 8 & 0xFF) * (1 - shape->reflection) +
					(reflected_color >> 8 & 0xFF) * shape->reflection;
	rgb_ref[2] = (color & 0xFF) * (1 - shape->reflection) +
					(reflected_color & 0xFF) * shape->reflection;
	return ((rgb_ref[0] << 16) | (rgb_ref[1] << 8) | rgb_ref[2]);
}

void		get_normal(t_shape *shape, t_rt *rt, t_coord *dir, int depth)
{
	if (depth == rt->depth)
		get_intersection_point(&rt->camera, dir, rt->t_closest, &shape->surface_point);
	else
		get_intersection_point(rt->source_point, dir, rt->t_closest, &shape->surface_point);
	if (shape->figure == PLANE || shape->figure == TRIANGLE || shape->figure == DISK)
		get_normal_plane(shape, dir);
	else if (shape->figure == SPHERE)
		get_normal_sphere(shape);
	else if (shape->figure == CYLINDER)
		get_normal_cylinder(shape);
	else if (shape->figure == CONE)
		get_normal_cone(shape, shape->angle);
}

/*void	ft_swap_new(double *a, double *b)
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

	*ref_r = (t_coord) {0, 0, 0};
	etai = 1.0;
	etat = shape->refract;
	normal = shape->normal;
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

int refract_color(t_coord *dir, t_shape *shape, t_rt *rt)
{
	int	trans_color;
	t_coord ref_r;

	refract_ray(dir, shape, &ref_r);
	rt->source_point = &shape->surface_point;
	trans_color = trace_ray(&ref_r, rt, 0);
	return (trans_color);
}*/

int			get_color(t_shape *shape, t_rt *rt, t_coord *dir, int depth)
{
	int		rgb[3];
	double	light;
	int		color;
	int		reflected_color;
	int		refracted_color;

	reflected_color = 0;
	refracted_color = 0;
	get_normal(shape, rt, dir, depth);
	rt->source_point = &shape->surface_point;
	light = get_light(shape, rt, dir);
	rgb[0] = (shape->color >> 16 & 0xFF) * light;
	rgb[1] = (shape->color >> 8 & 0xFF) * light;
	rgb[2] = (shape->color & 0xFF) * light;
	color = check_color(rgb);
	/*if (shape->refract)
	{
		refracted_color = refract_color(dir, shape, rt);
	}*/
	if (shape->reflection && depth > 0)
	{
		reflected_color = reflection(dir, shape, rt, depth - 1);
		color = reflect_color(color, reflected_color, shape);
	}
	return (color);
}
