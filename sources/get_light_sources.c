/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_light_sources.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 10:13:20 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/07 18:57:18 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int		get_light_type(char *str)
{
	if (ft_strequ(str, "point"))
		return (1);
	else if (ft_strequ(str, "directional"))
		return (2);
	else if (ft_strequ(str, "ambient"))
		return (3);
	else
		return (0);
}

static t_light	*init_light(char **line)
{
	int		i;
	t_light	*light;

	i = 0;
	while (line[i] != NULL)
		i++;
	if (i != 5)
		return (NULL);
	light = (t_light *)malloc(sizeof(t_light));
	if ((light->type = get_light_type(*line++)) == 0)
		return (NULL);
	light->point.x = ft_atof(*line++);
	light->point.y = ft_atof(*line++);
	light->point.z = ft_atof(*line++);
	light->intensity = ft_atof(*line);
	light->next = NULL;
	while (*line != NULL)
	{
		free(*line);
		line++;
	}
	return (light);
}

static void		free_list(t_light *head, t_rt *rt)
{
	t_light	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(head);
	}
	ft_putstr("\033[0;31m");
	ft_putstr("valid parameter(s) light:\n[point/directional/ambient]\
	[intensity] [x] [y] [z]\n");
	free_args(rt->head_shapes, NULL);
	exit(1);
}

static void		push_back_light(t_light **head, t_light *new, t_rt *rt)
{
	t_light	*tmp;

	if (new == NULL)
		free_list(*head, rt);
	if (*head == NULL)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_light			*get_light_sources(char *file_name, t_rt *rt)
{
	int		fd;
	char	*line;
	t_light	*head;

	head = NULL;
	if ((fd = open(file_name, O_RDONLY)) < 0)
	{
		perror(file_name);
		free_args(rt->head_shapes, NULL);
		exit(1);
	}
	while (get_next_line(fd, &line))
		push_back_light(&head, init_light(ft_strsplit(line, ' ')), rt);
	close(fd);
	return (head);
}
