/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 10:24:00 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/16 14:13:49 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		identify_shape(char *start, char *end)
{
	size_t	len;

	len = end - start;
	if (ft_strnstr(start, "plane", len))
		return (PLANE);
	else if (ft_strnstr(start, "sphere", len))
		return (SPHERE);
	else if (ft_strnstr(start, "cylinder", len))
		return (CYLINDER);
	else if (ft_strnstr(start, "cone", len))
		return (CONE);
	else if (ft_strnstr(start, "disk", len))
		return (DISK);
	else if (ft_strnstr(start, "triangle", len))
		return (TRIANGLE);
	else if (ft_strnstr(start, "torus", len))
		return (TORUS);
	else if (ft_strnstr(start, "capsule", len))
		return (CAPSULE);
	else if (ft_strnstr(start, "box", len))
		return (BOX);
	else if (ft_strnstr(start, "elipsoid", len))
		return (ELIPSIOD);
	else if (ft_strnstr(start, "fractal", len))
		return (FRACTAL);
	else
	{
		ft_putendl(U_SHAPE PFCF);
		exit(1);
	}
}

static t_vec3		identify_color(char *start, char *end)
{
	size_t	len;

	len = end - start;
	if (ft_strnstr(start, "red", end - start))
		return ((t_vec3){255, 0, 0});
	else if (ft_strnstr(start, "green", end - start))
		return ((t_vec3){0, 255, 0});
	else if (ft_strnstr(start, "blue", end - start))
		return ((t_vec3){0, 0, 255});
	else if (ft_strnstr(start, "yellow", end - start))
		return ((t_vec3){255, 255, 0});
	else if (ft_strnstr(start, "purple", end - start))
		return ((t_vec3){0, 255, 255});
	else if (ft_strnstr(start, "white", end - start))
		return ((t_vec3){255, 255, 255});
	else
	{
		ft_putendl(U_COLOR PFCF);
		exit(1);
	}
}

void			init_function_texture(t_shape *new)
{
	if (new->figure == PLANE)
		new->map_texture = &plane_texture;
	else if (new->figure == SPHERE || new->figure == ELIPSIOD)
		new->map_texture = &sphere_texture;
	else if (new->figure == CYLINDER)
		new->map_texture = &cylinder_texture;
	else if (new->figure == CONE)
		new->map_texture = &cone_texture;
	else if (new->figure == TORUS)
		new->map_texture = &torus_texture;
	else if (new->figure == BOX || new->figure == FRACTAL)
		new->map_texture = &box_texture;
	//else if (new->figure == CAPSULE)
		//new->map_texture = &gd_capsule;
}

void			init_function(t_shape *new)
{
	if (new->figure == PLANE)
		new->gd_fun = &gd_plane;
	else if (new->figure == SPHERE)
		new->gd_fun = &gd_sphere;
	else if (new->figure == CYLINDER)
		new->gd_fun = &gd_cylinder;
	else if (new->figure == CONE)
		new->gd_fun = &gd_cone;
	else if (new->figure == TORUS)
		new->gd_fun = &gd_torus;
	else if (new->figure == BOX)
		new->gd_fun = &gd_box;
	else if (new->figure == CAPSULE)
		new->gd_fun = &gd_capsule;
	else if (new->figure == ELIPSIOD)
		new->gd_fun = &gd_elispoid;
	else if (new->figure == FRACTAL)
		new->gd_fun = &gd_fractal;
}

void			init_shape_color(char *s, t_shape *new)
{
	char	*start;
	char	*end;
	//char	*str;

	if ((start = ft_strstr(s, "shape")) == NULL)
	{
		ft_putendl(M_SHAPE PFCF);
		exit(1);
	}
	end = ft_strchr(start, ',');
	new->figure = identify_shape(++start, end);
	if ((start = ft_strstr(s, "color")) == NULL)
	{
		ft_putendl(M_COLOR PFCF);
		exit(1);
	}
	end = ft_strchr(start, ',');
	new->color = identify_color(++start, end);
}

void			init_spec_refl(char *s, t_shape *new)
{
	char	*start;
	char	*str;

	if ((start = ft_strstr(s, "specular")) == NULL)
		new->specular = 0.0;
	else
	{
		if ((str = ft_strextract(start, ':', ',')) == NULL)
			str = ft_strextract(start, ':', '\0');
		new->specular = ft_atof(str);
		free(str);
	}
	if ((start = ft_strstr(s, "reflection")) == NULL)
		new->reflection = 0.0;
	else
	{
		if ((str = ft_strextract(start, ':', ',')) == NULL)
			str = ft_strextract(start, ':', '\0');
		new->reflection = ft_atof(str);
		free(str);
	}
}
