/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:29:21 by lwyl-the          #+#    #+#             */
/*   Updated: 2019/04/08 15:21:21 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*static int	check_color(int rgb[3])
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

static int	refract_color(int color, int refracted_color)
{
	int		rgb_ref[3];
	color = 0;

	rgb_ref[0] = (refracted_color >> 16 & 0xFF);
	rgb_ref[1] = (refracted_color >> 8 & 0xFF);
	rgb_ref[2] = (refracted_color & 0xFF);
	return ((rgb_ref[0] << 16) | (rgb_ref[1] << 8) | rgb_ref[2]);
}

static int	reflect_color(int color, int reflected_color, t_shape *shape)
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
	if (shape->figure == SPHERE)
		get_normal_sphere(shape);
	else if (shape->figure == CYLINDER)
		get_normal_cylinder(shape);
	else if (shape->figure == CONE)
		get_normal_cone(shape, shape->angle);
	else
		get_normal_plane(shape, dir);
}*/

//int			get_color(t_shape *shape, t_rt *rt, t_coord *dir, int depth)
//{
	//int		rgb[3];
	//double	light;
	//int		color = 0;
	//int		new_color = 0;
//
	//get_normal(shape, rt, dir, depth);
	//rt->source_point = &shape->surface_point;
	//light = get_light(shape, rt, dir);
	//light += path_tracing(shape, rt, depth);
	/*if (shape->texture != NULL)
	{
		if (shape->figure == SPHERE)
			shape->color = sphere_texture(shape->texture, shape);
		else if (shape->figure == CYLINDER || shape->figure == CONE)
			shape->color = cylinder_texture(shape, rt);
		else
			shape->color = plane_texture(shape->texture, shape);
	}*/
	//rgb[0] = (shape->color >> 16 & 0xFF) * light;
	//rgb[1] = (shape->color >> 8 & 0xFF) * light;
	//rgb[2] = (shape->color & 0xFF) * light;
	//color = check_color(rgb);
	//new_color = path_tracing(shape, rt, depth - 1);
	//rgb[0] = (color >> 16 & 0xFF) * 0.85 + (new_color >> 16 & 0xFF) * 0.15;
	//rgb[1] = (color >> 8 & 0xFF) * 0.85 + (new_color >> 8 & 0xFF) * 0.15;
	//rgb[2] = (color & 0xFF) * 0.85 + (new_color & 0xFF) * 0.15;
	//color = ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
	//color = check_color(rgb);
	/*if (shape->refract > 0)
	{
		new_color = refraction(dir, shape, rt, depth - 1);
		color = refract_color(color, new_color);
	}
	if (shape->reflection && depth > 0)
	{
		new_color = reflection(dir, shape, rt, depth - 1);
		color = reflect_color(color, new_color, shape);
	}*/
	//return (color);
//}

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

static int	reflect_color(int color, int reflected_color, double reflection)
{
	int		rgb_ref[3];

	rgb_ref[0] = (color >> 16 & 0xFF) * (1 - reflection) +
					(reflected_color >> 16 & 0xFF) * reflection;
	rgb_ref[1] = (color >> 8 & 0xFF) * (1 - reflection) +
					(reflected_color >> 8 & 0xFF) * reflection;
	rgb_ref[2] = (color & 0xFF) * (1 - reflection) +
					(reflected_color & 0xFF) * reflection;
	return ((rgb_ref[0] << 16) | (rgb_ref[1] << 8) | rgb_ref[2]);
}

#include <stdlib.h>
#include <stdio.h>

typedef struct		s_hsv_color
{
    unsigned char	h;
    unsigned char	s;
    unsigned char	v;
}					t_hsv_color;

typedef struct		s_rgb_color
{
    unsigned char	r;
    unsigned char	g;
    unsigned char	b;
}					t_rgb_color;

t_hsv_color	ft_rgb_to_hsv(t_rgb_color rgb)
{
    t_hsv_color		hsv;
    unsigned char	rgb_min;
	unsigned char	rgb_max;

	rgb_min = ft_dmin(rgb.r, ft_dmin(rgb.g, rgb.b));
	rgb_max = ft_dmax(rgb.r, ft_dmax(rgb.g, rgb.b));

    hsv.v = rgb_max;
    if (hsv.v == 0)
    {
        hsv.h = 0;
        hsv.s = 0;
        return hsv;
    }

    hsv.s = 255 * (long)(rgb_max - rgb_min) / hsv.v;
    if (hsv.s == 0)
    {
        hsv.h = 0;
        return hsv;
    }

    if (rgb_max == rgb.r)
        hsv.h = 0 + 43 * (rgb.g - rgb.b) / (rgb_max - rgb_min);
    else if (rgb_max == rgb.g)
        hsv.h = 85 + 43 * (rgb.b - rgb.r) / (rgb_max - rgb_min);
    else
        hsv.h = 171 + 43 * (rgb.r - rgb.g) / (rgb_max - rgb_min);

    return hsv;
}

t_rgb_color ft_hsv_to_rgb(t_hsv_color hsv)
{
    t_rgb_color rgb;
    unsigned char region, remainder, p, q, t;

    if (hsv.s == 0)
        return ((t_rgb_color){hsv.v, hsv.v, hsv.v});

    region = hsv.h / 43;
    remainder = (hsv.h - (region * 43)) * 6; 

    p = (hsv.v * (255 - hsv.s)) >> 8;
    q = (hsv.v * (255 - ((hsv.s * remainder) >> 8))) >> 8;
    t = (hsv.v * (255 - ((hsv.s * (255 - remainder)) >> 8))) >> 8;

	if (region == 0)
		rgb = (t_rgb_color){hsv.v, t, p};
	else if (region == 1)
		rgb = (t_rgb_color){q, hsv.v, p};
	else if (region == 2)
		rgb = (t_rgb_color){p, hsv.v, t};
	else if (region == 3)
		rgb = (t_rgb_color){p, q, hsv.v};
	else if (region == 4)
		rgb = (t_rgb_color){t, p, hsv.v};
	else
		rgb = (t_rgb_color){hsv.v, p, q};
    return rgb;
}

void	ft_set_color_invers_hsv(t_shape *shape, int rgb_m[3], double light)
{
	int	max_rgb;
	int min_rgb;
	t_hsv_color	hsv;
	t_rgb_color rgb;

	rgb_m[0] = (shape->color >> 16 & 0xFF) * light;
	rgb_m[1] = (shape->color >> 8 & 0xFF) * light;
	rgb_m[2] = (shape->color & 0xFF) * light;
	rgb = (t_rgb_color){rgb_m[0], rgb_m[1], rgb_m[2]};
	hsv = ft_rgb_to_hsv(rgb);
	hsv.h = 360 - hsv.h;
	rgb = ft_hsv_to_rgb(hsv);
	rgb_m[0] = rgb.r;
	rgb_m[1] = rgb.g;
	rgb_m[2] = rgb.b;
}

void	ft_set_color_grey(t_shape *shape, int rgb_m[3], double light)
{
	int	color;
	rgb_m[0] = (shape->color >> 16 & 0xFF);
	rgb_m[1] = (shape->color >> 8 & 0xFF);
	rgb_m[2] = (shape->color & 0xFF);
	color = (rgb_m[0] + rgb_m[1] + rgb_m[2]) / 3;
	rgb_m[0] = (color) * light;
	rgb_m[1] = (color) * light;
	rgb_m[2] = (color) * light;
}

void	ft_set_color_invers(t_shape *shape, int rgb_m[3], double light)
{
	rgb_m[0] = 0xFF - ((shape->color >> 16 & 0xFF)) * light;
	rgb_m[1] = 0xFF - ((shape->color >> 8 & 0xFF)) * light;
	rgb_m[2] = 0xFF - ((shape->color & 0xFF)) * light;
}

void	ft_set_color_toon_shading(t_shape *shape, int rgb_m[3], double light)
{
	if (light < 0.3)
		light = 0.3;
	else if (light < 0.7)
		light = 0.7;
	else
		light = 1.0;
	rgb_m[0] = (shape->color >> 16 & 0xFF) * light;
	rgb_m[1] = (shape->color >> 8 & 0xFF) * light;
	rgb_m[2] = (shape->color & 0xFF) * light;
}

void	ft_set_color(t_shape *shape, int rgb_m[3], double light)
{
	rgb_m[0] = (shape->color >> 16 & 0xFF) * light;
	rgb_m[1] = (shape->color >> 8 & 0xFF) * light;
	rgb_m[2] = (shape->color & 0xFF) * light;
}

int		get_color(t_vec3 *dir, t_shape *shape, t_rt *rt, int depth)
{
	int		rgb[3];
	double	light;
	double	color;
	double	new_color;

	get_intersection_point(rt->source_point, dir, rt->t_closest, &shape->surface_point);
	get_normal(shape);
	light = get_light(dir, shape, rt);
	//light = emission(shape, rt, depth);

	ft_set_color_toon_shading(shape, rgb, light);

	color = check_color(rgb);

	//ADDING REFLECTION
	/*if (depth > 0 && shape->reflection)
	{
		new_color = reflection(dir, shape, rt, depth - 1);
		color = reflect_color(color, new_color, shape->reflection);
	}*/
	//END

	return (color);
}
