/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 11:26:38 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/15 12:03:55 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static char	*get_end(char *s, int c_s, int c_e)
{
	int		pair;
	char	c;

	pair = 0;
	while ((c = *s) != '\0') //&& (c != c_e && pair != 0))
	{
		if (c == c_s)
			++pair;
		else if (c == c_e)
		{
			if (pair == 0)
				return (s);
			--pair;
		}
		++s;
	}
	//printf("str - %s\n", s);
	//printf("str - %s\n", s);
	return (NULL);
}

//static char	*get_end(char *s, int c_s, int c_e, int pair)
//{
	//printf("\n\npair - %d\n", pair);
	//while (s != NULL && *s != '\0' && *s != c_e)
	//{
		//printf("cur_char - %c\n", *s);
		//if (*s == c_s)
		//{
			//s = get_end(s + 1, c_s, c_e, pair + 1);
			//if (s == NULL)
				//return (NULL);
		//}
		//s++;
	//}
	//printf("str - %s\n", s);
	//if (pair != 0)
		//s = get_end(s + 1, c_s, c_e, pair - 1);
	//printf("str - %s\n", s);
	//if (s == NULL || *s == '\0')
		//return (NULL);
	//return (s);
//}

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

	char	*end;

	if (*file != '{' || (end = get_end(file + 1, '{', '}')) == NULL || *(end + 1) != '\0')
		return (1);
	//printf("start - %c\n", *file);
	//printf("end - %s\n", get_end(file + 1, '{', '}'));

















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
