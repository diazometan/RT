/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 10:24:00 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/08 13:52:35 by rrhaenys         ###   ########.fr       */
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
	else if (ft_strnstr(start, "intersect", len))
		return (INTERSECT);
	else if (ft_strnstr(start, "unite", len))
		return (UNITE);
	else if (ft_strnstr(start, "difference", len))
		return (DIFFERENCE);
	else if (ft_strnstr(start, "half_space", len))
		return (HALF_SPACE);
	else
	{
		ft_putendl(U_SHAPE PFCF);
		exit(1);
	}
}

static int		identify_color(char *start, char *end)
{
	size_t	len;

	len = end - start;
	if (ft_strnstr(start, "red", end - start))
		return (RED);
	else if (ft_strnstr(start, "green", end - start))
		return (GREEN);
	else if (ft_strnstr(start, "blue", end - start))
		return (BLUE);
	else if (ft_strnstr(start, "yellow", end - start))
		return (YELLOW);
	else if (ft_strnstr(start, "purple", end - start))
		return (PURPLE);
	else
	{
		ft_putendl(U_COLOR PFCF);
		exit(1);
	}
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
	else if (new->figure == INTERSECT)
		new->gd_fun = &intersect;
	else if (new->figure == UNITE)
		new->gd_fun = &unite;
	else if (new->figure == DIFFERENCE)
		new->gd_fun = &difference;
	else if (new->figure == HALF_SPACE)
		new->gd_fun = &gd_half_space;
}

void			init_id(char *s, t_shape *new)
{
	char	*start;
	char	*str;

	start = ft_strstr(s, "id");
	if (start == NULL)
	{
		ft_putendl(M_ID PFCF);
		exit(1);
	}
	if ((str = ft_strextract(start, ':', ',')) == NULL)
		str = ft_strextract(start, ':', '\0');
	new->id = ft_atof(str);
	free(str);
}


void			init_shape_child(t_shape *new, t_shape *shape1, t_shape *shape2)
{
	new->f_is_in_group = 0;
	new->shape1 = shape1;
	new->shape2 = shape2;
	new->f_is_group = (new->shape1 != NULL && new->shape2 != NULL);
	if (new->shape1 != NULL)
		new->shape1->f_is_in_group = 1;
	if (new->shape2 != NULL)
		new->shape2->f_is_in_group = 1;
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
