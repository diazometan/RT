/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 10:24:00 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/18 10:27:28 by rgyles           ###   ########.fr       */
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
	else
	{
		ft_putendl("\033[0;31mUndefined shape detected!\033[0m");
		ft_putendl("Please fix config file");
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
		ft_putendl("\033[0;31mUndefined color detected!\033[0m");
		ft_putendl("Please fix config file");
		exit(1);
	}
}

void			init_shape_color(char *s, t_shape *new)
{
	char	*start;
	char	*end;
	//char	*str;

	if ((start = ft_strstr(s, "shape")) == NULL)
	{
		ft_putendl("\033[0;31mShape identifier is missing!\033[0m");
		ft_putendl("Please fix config file");
		exit(1);
	}
	end = ft_strchr(start, ',');
	new->figure = identify_shape(++start, end);
	if ((start = ft_strstr(s, "color")) == NULL)
	{
		ft_putendl("\033[0;31mColor identifier is missing!\033[0m");
		ft_putendl("Please fix config file");
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
	{
		ft_putendl("\033[0;31mSpecular field missing!\033[0m");
		ft_putendl("Please fix config file");
		exit(1);
	}
	if ((str = ft_strextract(start, ':', ',')) == NULL)
		str = ft_strextract(start, ':', '}');
	new->specular = ft_atof(str);
	free(str);
	if ((start = ft_strstr(s, "reflection")) == NULL)
	{
		ft_putendl("\033[0;31mReflection field missing!\033[0m");
		ft_putendl("Please fix config file");
		exit(1);
	}
	if ((str = ft_strextract(start, ':', ',')) == NULL)
		str = ft_strextract(start, ':', '}');
	new->reflection = ft_atof(str);
	free(str);
}
