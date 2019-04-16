/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 11:26:38 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/16 20:11:03 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

//int			check_number(char *n)
//{
	//int		flag;
	//char	c;
//
	//flag = 0;
	//while ((c = *n) != '\0' && c >= '0' && c <= '9')
	//{
		//if (c == '.')
			//++flag;
		//if (flag > 1)
			//return (1);
		//++n;
	//}
	//if (c != '\0')
		//return (1);
	//return (0);
//}

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
	//extract_coord(str, &rt->camera);
	free(str);
	if ((start = ft_strstr(s, "direction")) == NULL)
	{
		ft_putendl(M_DIR PFCF);
		exit(1);
	}
	str = ft_strextract(start, '[', ']');
	//extract_coord(str, &rt->angle);
	rt->angle.x = M_PI * rt->angle.x / 180;
	rt->angle.y = M_PI * rt->angle.y / 180;
	rt->angle.z = M_PI * rt->angle.z / 180;
	free(str);
}

int		init_config(char *file, t_rt *rt)
{
	char	*start;
	//char	*shapes;
	//char	*lighting;
	//char	*camera;
	//char	*physics;

	char	*end;

	if (*file != '{' || (end = get_end(file + 1, '{', '}')) == NULL || *(end + 1) != '\0')
		return (1);
	if ((start = ft_strnstr(file + 1, "\"scene\":", 8)) == NULL)
		return (1);
	start += 8;
	//printf("\n\nstr - %s\n", start);
	if (*start != '{' || get_end(start + 1, '{', '}') == NULL)
		return (1);

	//INIT SHAPES
	if ((start = ft_strnstr(start + 1, "\"objects\":", 10)) == NULL)
		return (1);
	start += 10;
	if (*start != '[' || (end = get_end(start + 1, '[', ']')) == NULL || *(end + 1) != ',')
	{
		ft_putendl(OBJ M_MATCH PFCF);
		return (1);
	}
	//printf("check\n");
	if ((start = init_shapes(start + 1, &rt->head_shapes, &rt->head_textures)) == NULL || *start != ',')
		return (1);


	//INIT LIGHTING
	if ((start = ft_strnstr(start + 1, "\"lighting\":", 11)) == NULL)
		return (1);
	start += 11;
	if (*start != '[' || (end = get_end(start + 1, '[', ']')) == NULL || *(end + 1) != ',')
	{
		ft_putendl(LIGHT M_MATCH PFCF);
		return (1);
	}
	if ((start = init_lighting(start + 1, &rt->head_light)) == NULL || *start != ',')
		return (1);
	//printf("\n\nstart after init_shapes - %s\n", start);
	//printf("start - %c\n", *file);
	//printf("end - %s\n", get_end(file + 1, '{', '}'));

















	//if ((start = ft_strstr(file, "\"objects\"")) == NULL)
		//return (1);
	//shapes = ft_strextract(start, '[', ']');
	//init_shapes(shapes, &rt->head_shapes, &rt->head_textures);
	//if ((start = ft_strstr(file, "lighting")) == NULL)
		//return (1);
	//lighting = ft_strextract(start, '[', ']');
	//init_lighting(lighting, &rt->head_light);
	//if ((start = ft_strstr(file, "camera")) == NULL)
		//return (1);
	//camera = ft_strextract(start, '{', '}');
	//init_camera(camera, rt);
	//if ((start = ft_strstr(file, "physics")) == NULL)
		//return (1);
	//physics = ft_strextract(start, '{', '}');
	//init_physics(physics, rt);
	return (0);
}
