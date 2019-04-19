/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 11:26:38 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/02 20:33:56 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		extract_coord(char *str, t_vec3 *p)
{
	int		i;
	char	**array;

	i = 0;
	array = ft_strsplit(str, ',');
	while (array[i] != NULL)
		i++;
	if (i != 3)
	{
		ft_putendl(U_COORD PFCF);
		exit(1);
	}
	p->x = ft_atof(array[0]);
	p->y = ft_atof(array[1]);
	p->z = ft_atof(array[2]);
}

void	init_camera(char *s, t_rt *rt)
{
	char	*str;
	char	*start;

	if ((start = ft_strstr(s, "center")) == NULL)
	{
		ft_putendl(M_CENTER PFCF);
		exit(1);
	}
	str = ft_strextract(start, '[', ']');
	extract_coord(str, &rt->camera);
	free(str);
	if ((start = ft_strstr(s, "direction")) == NULL)
	{
		ft_putendl(M_DIR PFCF);
		exit(1);
	}
	str = ft_strextract(start, '[', ']');
	extract_coord(str, &rt->angle);
	rt->angle.x = M_PI * rt->angle.x / 180;
	rt->angle.y = M_PI * rt->angle.y / 180;
	rt->angle.z = M_PI * rt->angle.z / 180;
	free(str);
}

int		init_config(char *file, t_rt *rt)
{
	char	*start;
	char	*shapes;
	char	*lighting;
	char	*camera;
	char	*physics;

	if ((start = ft_strstr(file, "objects")) == NULL)
		return (1);
	shapes = ft_strextract(start, '[', ']');
	init_shapes(shapes, &rt->head_shapes, &rt->head_textures);
	if ((start = ft_strstr(file, "lighting")) == NULL)
		return (1);
	lighting = ft_strextract(start, '[', ']');
	init_lighting(lighting, &rt->head_light);
	if ((start = ft_strstr(file, "camera")) == NULL)
		return (1);
	camera = ft_strextract(start, '{', '}');
	init_camera(camera, rt);
	if ((start = ft_strstr(file, "physics")) == NULL)
		return (1);
	physics = ft_strextract(start, '{', '}');
	init_physics(physics, rt);
	return (0);
}
