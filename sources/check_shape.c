/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_shape.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 18:06:18 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/11 19:17:14 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		init_color(char *str)
{
	if (ft_strequ(str, "red"))
		return (0xFF0000);
	else if (ft_strequ(str, "blue"))
		return (0x0000FF);
	else if (ft_strequ(str, "lime"))
		return (0x00FF00);
	else if (ft_strequ(str, "green"))
		return (0x008000);
	else if (ft_strequ(str, "yellow"))
		return (0xFFFF00);
	else if (ft_strequ(str, "purple"))
		return (0x800080);
	else if (ft_strequ(str, "grey"))
		return (0x808080);
	else if (ft_strequ(str, "maroon"))
		return (0x800000);
	else if (ft_strequ(str, "aqua"))
		return (0x00FFFF);
	else
		return (-1);
}

static int		get_figure(char *str)
{
	if (ft_strequ(str, "plane"))
		return (PLANE);
	else if (ft_strequ(str, "sphere"))
		return (SPHERE);
	else if (ft_strequ(str, "cylinder"))
		return (CYLINDER);
	else if (ft_strequ(str, "cone"))
		return (CONE);
	else
		return (0);
}

int				check_shape(t_shape *shape, char **line)
{
	int	i;

	i = 0;
	if (line == NULL)
		return (1);
	if ((shape->figure = get_figure(line[0])) == 0)
		return (1);
	while (line[i] != NULL)
		i++;
	if (i != 11)
		return (1);
	if ((shape->color = init_color(line[1])) == -1)
		return (1);
	i = 2;
	shape->radius = ft_atof(line[i++]);
	shape->angle = (M_PI * ft_atoi(line[i++])) / 180;
	shape->reflection = ft_atof(line[i++]);
	shape->center.x = ft_atof(line[i++]);
	shape->center.y = ft_atof(line[i++]);
	shape->center.z = ft_atof(line[i++]);
	shape->unit.x = ft_atof(line[i++]);
	shape->unit.y = ft_atof(line[i++]);
	shape->unit.z = ft_atof(line[i]);
	return (0);
}
