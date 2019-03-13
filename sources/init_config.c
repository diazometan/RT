/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 11:26:38 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/13 20:16:21 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		extract_coord(char *str, t_coord *coord)
{
	int		i;
	char	**array;

	i = 0;
	array = ft_strsplit(str, ',');
	while (array[i] != NULL)
		i++;
	if (i != 3)
	{
		printf("error!\n");
		exit(1);
	}
	coord->x = ft_atof(array[0]);
	coord->y = ft_atof(array[1]);
	coord->z = ft_atof(array[2]);
}

void	get_camera(char *s, t_rt *rt)
{
	char	*str;
	char	*start;

	start = ft_strstr(s, "center");
	str = ft_strextract(start, '[', ']');
	extract_coord(str, &rt->camera);
	free(str);
	start = ft_strstr(s, "direction");
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

	if ((start = ft_strstr(file, "objects")) == NULL)
		return (1);
	shapes = ft_strextract(start, '[', ']');
	//printf("\nobjects - %s\n\n", shapes);
	get_shapes(shapes, &rt->head_shapes);
	if ((start = ft_strstr(file, "lighting")) == NULL)
		return (1);
	lighting = ft_strextract(start, '[', ']');
	//printf("light - %s\n\n", lighting);
	get_lighting(lighting, &rt->head_light);
	if ((start = ft_strstr(file, "camera")) == NULL)
		return (1);
	camera = ft_strextract(start, '{', '}');
	get_camera(camera, rt);
	//printf("camera - %s\n\n", camera);
	return (0);
}
