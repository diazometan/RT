/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 11:26:38 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/17 12:43:38 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	init_reflection_depth(char *s, int *depth)
{
	if ((s = ft_strstr(s, "\"reflection_depth\"")) == NULL || *(s + 18) != ':')
	{
		ft_putendl(M_DEPTH);
		exit(1);
	}
	else if ((*depth = (int)get_double(s + 19, ',')) < 0 || *depth > 5)
	{
		ft_putendl(U_DEPTH);
		exit(1);
	}
}

static void	init_pixel_division(char *s, int *p_division)
{
	if ((s = ft_strstr(s, "\"pixel_division\"")) == NULL || *(s + 16) != ':')
	{
		ft_putendl(M_PDIV);
		exit(1);
	}
	else if ((*p_division = (int)get_double(s + 17, ',')) < 0 || *p_division > 5)
	{
		ft_putendl(U_PDIV);
		exit(1);
	}
}

static void	init_physics(char *s, t_rt *rt)
{
	char	*end;

	end = get_end(s + 1, '{', '}');
	*end = '\0';
	init_pixel_division(s, &rt->p_division);
	init_reflection_depth(s, &rt->depth);
	rt->sample_step = 1.0 / rt->p_division;
	rt->sample_center = rt->sample_step / 2.0;
}

static char	*init_camera(char *s, t_vec3 *camera, t_vec3 *angle)
{
	char	*end;

	end = get_end(s + 1, '{', '}');
	*end = '\0';
	init_center(s, camera);
	init_direction(s, angle, NULL);
	vec3_scalar(angle, M_PI / 180.0);
	return (end + 1);
}

int		init_config(char *file, t_rt *rt)
{
	char	*start;
	char	*end;

	if (*file != '{' || (end = get_end(file + 1, '{', '}')) == NULL || *(end + 1) != '\0')
		return (1);
	if ((start = ft_strnstr(file + 1, "\"scene\":", 8)) == NULL)
		return (1);
	start += 8;
	if (*start != '{' || get_end(start + 1, '{', '}') == NULL)
		return (1);
	if ((start = ft_strnstr(start + 1, "\"objects\":", 10)) == NULL)
		return (1);
	start += 10;
	if (*start != '[' || (end = get_end(start + 1, '[', ']')) == NULL || *(end + 1) != ',')
	{
		ft_putendl(M_MATCH);
		return (1);
	}
	if ((start = init_shapes(start + 1, &rt->head_shapes, &rt->head_textures)) == NULL || *start != ',')
		return (1);
	if ((start = ft_strnstr(start + 1, "\"lighting\":", 11)) == NULL)
		return (1);
	start += 11;
	if (*start != '[' || (end = get_end(start + 1, '[', ']')) == NULL || *(end + 1) != ',')
	{
		ft_putendl(M_MATCH);
		return (1);
	}
	if ((start = init_lighting(start + 1, &rt->head_light)) == NULL || *start != ',')
		return (1);
	if ((start = ft_strnstr(start + 1, "\"camera\":", 9)) == NULL)
		return (1);
	start += 9;
	if (*start != '{' || (end = get_end(start + 1, '{', '}')) == NULL || *(end + 1) != ',')
	{
		ft_putendl(M_MATCH);
		return (1);
	}
	if ((start = init_camera(start + 1, &rt->camera, &rt->angle)) == NULL || *start != ',')
		return (1);
	if ((start = ft_strnstr(start + 1, "\"physics\":", 10)) == NULL)
		return (1);
	start += 10;
	if (*start != '{' || (end = get_end(start + 1, '{', '}')) == NULL || *(end + 1) != '}')
	{
		ft_putendl(M_MATCH);
		return (1);
	}
	init_physics(start + 1, rt);
	return (0);
}
