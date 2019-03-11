/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 18:27:53 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/11 19:18:23 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	check_camera(char **line, t_rt *rt)
{
	int	i;

	i = 0;
	if (line == NULL)
		return (1);
	while (line[i] != NULL)
		i++;
	if (i != 4)
		return (1);
	if (!ft_strequ(line[0], "camera"))
		return (1);
	rt->camera.x = ft_atof(line[1]);
	rt->camera.y = ft_atof(line[2]);
	rt->camera.z = ft_atof(line[3]);
	return (0);
}

static int	check_angle(char **line, t_rt *rt)
{
	int	i;

	i = 0;
	if (line == NULL)
		return (1);
	while (line[i] != NULL)
		i++;
	if (i != 3)
		return (1);
	if (!ft_strequ(line[0], "angle"))
		return (1);
	rt->alpha = M_PI * ft_atof(line[1]) / 180;
	rt->beta = M_PI * ft_atof(line[2]) / 180;
	return (0);
}

static void	exit_with_error(t_rt *rt)
{
	ft_putstr("\033[0;31m");
	ft_putstr("valid parameter camera:\n[camera] [x] [y] [z]\n\
[angle] [horizontal turn] [vertical turn]\n");
	free_args(rt->head_shapes, rt->head_light);
	exit(1);
}

void		init_camera(char *file_name, t_rt *rt)
{
	int		i;
	int		fd;
	char	*line;

	i = 0;
	if ((fd = open(file_name, O_RDONLY)) < 0)
	{
		perror(file_name);
		free_args(rt->head_shapes, rt->head_light);
		exit(1);
	}
	while (get_next_line(fd, &line))
	{
		i++;
		if (i == 1 && check_camera(ft_strsplit(line, ' '), rt))
			exit_with_error(rt);
		else if (i == 2 && check_angle(ft_strsplit(line, ' '), rt))
			exit_with_error(rt);
	}
	if (i != 2)
		exit_with_error(rt);
	close(fd);
}
