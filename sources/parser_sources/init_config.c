/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 11:26:38 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/17 17:55:54 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static char	*init_camera(char *s, t_vec3 *camera, t_vec3 *angle)
{
	char	*end;

	if ((s = ft_strnstr(s, "\"camera\":", 9)) == NULL)
		return (NULL);
	s += 9;
	if (*s != '{' || (end = get_end(s++ + 1, '{', '}')) == NULL ||
													*(end + 1) != ',')
	{
		ft_putendl(M_MATCH);
		return (NULL);
	}
	*end = '\0';
	init_center(s, camera);
	init_direction(s, angle, NULL);
	vec3_scalar(angle, M_PI / 180.0);
	return (end + 1);
}

static char	*validate_scene(char *s)
{
	char	*end;

	if (*s != '{' || (end = get_end(s + 1, '{', '}')) == NULL ||
												*(end + 1) != '\0')
		return (NULL);
	if ((s = ft_strnstr(s + 1, "\"scene\":", 8)) == NULL)
		return (NULL);
	s += 8;
	if (*s != '{' || get_end(s + 1, '{', '}') == NULL)
		return (NULL);
	if ((s = ft_strnstr(s + 1, "\"objects\":", 10)) == NULL)
		return (NULL);
	s += 10;
	if (*s != '[' || (end = get_end(s + 1, '[', ']')) == NULL ||
												*(end + 1) != ',')
	{
		ft_putendl(M_MATCH);
		return (NULL);
	}
	return (s);
}

static char	*validate_light(char *s)
{
	char	*end;

	if ((s = ft_strnstr(s + 1, "\"lighting\":", 11)) == NULL)
		return (NULL);
	s += 11;
	if (*s != '[' || (end = get_end(s + 1, '[', ']')) == NULL ||
												*(end + 1) != ',')
	{
		ft_putendl(M_MATCH);
		return (NULL);
	}
	return (s);
}

int			init_config(char *file, t_rt *rt)
{
	char	*start;

	if ((start = validate_scene(file)) == NULL)
		return (1);
	if ((start = init_shapes(start + 1,
			&rt->head_shapes, &rt->head_textures)) == NULL || *start != ',')
		return (1);
	if ((start = validate_light(start)) == NULL)
		return (1);
	if ((start = init_lighting(start + 1,
			&rt->head_light)) == NULL || *start != ',')
		return (1);
	if ((start = init_camera(start + 1, &rt->camera, &rt->angle)) == NULL ||
																*start != ',')
		return (1);
	if (init_physics(start + 1, rt))
		return (1);
	return (0);
}
