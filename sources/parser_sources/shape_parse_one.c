/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_parse_one.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 15:11:45 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/16 12:36:26 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

//static t_vec3		identify_color(char *start, char *end)
//{
	//size_t	len;
//
	//len = end - start;
	//if (ft_strnstr(start, "red", end - start))
		//return ((t_vec3){255, 0, 0});
	//else if (ft_strnstr(start, "green", end - start))
		//return ((t_vec3){0, 255, 0});
	//else if (ft_strnstr(start, "blue", end - start))
		//return ((t_vec3){0, 0, 255});
	//else if (ft_strnstr(start, "yellow", end - start))
		//return ((t_vec3){255, 255, 0});
	//else if (ft_strnstr(start, "purple", end - start))
		//return ((t_vec3){0, 255, 255});
	//else if (ft_strnstr(start, "white", end - start))
		//return ((t_vec3){255, 255, 255});
	//else
	//{
		//ft_putendl(U_COLOR PFCF);
		//exit(1);
	//}
//}
//
//
//void	init_center(char *s, t_shape *new)
//{
	//char	*start;
	//char	*str;
//
	//if ((start = ft_strstr(s, "center")) == NULL)
	//{
		//ft_putendl(M_CENTER PFCF);
		//exit(1);
	//}
	//str = ft_strextract(start, '[', ']');
	//extract_coord(str, &new->center);
	//free(str);
//}

void		identify_color(char *s, t_vec3 *color)
{
	char	*str;

	if ((str = ft_strstr(s, "\"color\"")) == NULL || *(str + 7) != ':')
	{
		ft_putendl(U_VEC PFCF);
		exit(1);
	}
	//if ((str = ft_strextract(str, '[', ']')) == NULL)
	//{
		//ft_putendl(MEMORY);
		//exit (1);
	//}
	get_vector(str + 8, color);
	if (color->x < 0 || color->x > 255 || color->y < 0
		|| color->y > 255 || color->z < 0 || color->z > 255)
	{
		ft_putendl(U_COLOR);
		exit(1);
	}
	//extract_coord(str, color);
	//free(str);
	//return (0);
}

int		identify_shape(char *start)
{
	if (ft_strcequ(start, "\"plane\"", ','))
		return (PLANE);
	else if (ft_strcequ(start, "\"sphere\"", ','))
		return (SPHERE);
	else if (ft_strcequ(start, "\"cylinder\"", ','))
		return (CYLINDER);
	else if (ft_strcequ(start, "\"infinite_cylinder\"", ','))
		return (INF_CYLINDER);
	else if (ft_strcequ(start, "\"cone\"", ','))
		return (CONE);
	else if (ft_strcequ(start, "\"infinite_cone\"", ','))
		return (CONE);
	else if (ft_strcequ(start, "\"torus\"", ','))
		return (TORUS);
	else if (ft_strcequ(start, "\"capsule\"", ','))
		return (CAPSULE);
	else if (ft_strcequ(start, "\"box\"", ','))
		return (BOX);
	else if (ft_strcequ(start, "\"elipsoid\"", ','))
		return (ELIPSIOD);
	else if (ft_strcequ(start, "\"fractal\"", ','))
		return (FRACTAL);
	else
		return (-1);
}
