/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shapes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 10:07:42 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/07 18:49:27 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_shape	*init_shape(char **line)
{
	t_shape	*shape;

	shape = NULL;
	if (line == NULL ||
		((shape = (t_shape *)malloc(sizeof(t_shape))) == NULL) ||
										check_shape(shape, line))
	{
		free(shape);
		return (NULL);
	}
	normalize_vector(&shape->unit, vector_length(&shape->unit));
	shape->next = NULL;
	while (*line != NULL)
	{
		free(*line);
		line++;
	}
	return (shape);
}

static void		free_list(t_shape *head)
{
	t_shape	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(head);
	}
	ft_putstr("\033[0;31m");
	ft_putstr("valid parameter(s) shape(s):\n[figure] \
[color] [radius] [angle] [reflection] \
[x0] [y0] [z0] [u_x] [u_y] [u_z]\n\n\
figures: plane / sphere / cylinder / cone\n\
colors: red / green / blue / lime / yellow \
/ purple / maroon / aqua / grey\n");
	exit(1);
}

static void		push_back_shape(t_shape **head, t_shape *new)
{
	t_shape	*tmp;

	if (new == NULL)
		free_list(*head);
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

t_shape			*get_shapes(char *file_name)
{
	int		fd;
	char	*line;
	t_shape	*head;

	head = NULL;
	if ((fd = open(file_name, O_RDONLY)) < 0)
	{
		perror(file_name);
		exit(1);
	}
	while (get_next_line(fd, &line))
		push_back_shape(&head, init_shape(ft_strsplit(line, ' ')));
	close(fd);
	return (head);
}
