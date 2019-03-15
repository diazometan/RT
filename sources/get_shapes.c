/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shapes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 16:16:02 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/14 20:29:42 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		push_back_shape(t_shape **head, t_shape *new)
{
	t_shape	*tmp;

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

void		create_caps(t_rt *rt)
{
	static 	int flag = 0;
	t_shape *tmp;

	tmp = rt->head_shapes;
	while (tmp && flag == 0)
	{
		if (tmp->figure == 3)
		{
			flag = 1;
			t_shape *disk_bot = (t_shape*)malloc(sizeof(t_shape));
			disk_bot->center = (t_coord){tmp->center.x, tmp->center.y, tmp->center.z};
			disk_bot->color = tmp->color;
			disk_bot->figure = 5;
			disk_bot->unit = (t_coord){tmp->unit.x, tmp->unit.y, tmp->unit.z};
			disk_bot->radius = 1;
			disk_bot->specular = 555;
			disk_bot->reflection = 123;
			disk_bot->next = NULL;
			push_back_shape(&rt->head_shapes, disk_bot);
			t_shape *disk_top = (t_shape*)malloc(sizeof(t_shape));
			normalize_vector(&tmp->unit, vector_length(&tmp->unit));
			double h = 1;
			disk_top->center = (t_coord){tmp->center.x + h * tmp->unit.x, tmp->center.y + h * tmp->unit.y, tmp->center.z + h * tmp->unit.z};
			disk_top->color = tmp->color;
			disk_top->figure = 5;
			disk_top->unit = (t_coord){tmp->unit.x, tmp->unit.y, tmp->unit.z};
			disk_top->radius = 1;
			disk_top->specular = 555;
			disk_top->reflection = 123;
			disk_top->next = NULL;
			push_back_shape(&rt->head_shapes, disk_top);
		}
		if (tmp->figure == 4)
		{
			t_shape *cone_disk = (t_shape*)malloc(sizeof(t_shape));
			double h = 1.0;
			normalize_vector(&tmp->unit, vector_length(&tmp->unit));
			cone_disk->center = (t_coord){tmp->center.x + h * tmp->unit.x, tmp->center.y + h * tmp->unit.y, tmp->center.z + h * tmp->unit.z};
			cone_disk->color = 0xFF;
			cone_disk->figure = 5;
			cone_disk->unit = (t_coord){tmp->unit.x, tmp->unit.y, tmp->unit.z};
			cone_disk->radius = h * tan(tmp->angle);
			cone_disk->specular = 555;
			cone_disk->reflection = 123;
			cone_disk->next = NULL;
			push_back_shape(&rt->head_shapes, cone_disk);
		}
		tmp = tmp->next;
	}
}

void	get_shapes(char *s, t_shape **head)
{
	int		i;
	char	*start;
	char	*end;
	char	*str;
	char	*object;
	t_shape	*new;

	(void)head;
	i = 1;
	while ((object = ft_strextract(s, '{', '}')) != NULL)
	{
		new = (t_shape *)malloc(sizeof(*new));
		new->next = NULL;
		//IDENTIFY SHAPE
		start = ft_strstr(s, "shape");
		start++;
		end = ft_strchr(start, ',');
		if (ft_strnstr(start, "plane", end - start))
			new->figure = PLANE;
		else if (ft_strnstr(start, "sphere", end - start))
			new->figure = SPHERE;
		else if (ft_strnstr(start, "cylinder", end - start))
			new->figure = CYLINDER;
		else if (ft_strnstr(start, "cone", end - start))
			new->figure = CONE;
		else if (ft_strnstr(start, "disk", end - start))
			new->figure = DISK;
		else if (ft_strnstr(start, "triangle", end - start))
			new->figure = TRIANGLE;
		else
		{
			printf("check config file for mistakes\n");
			exit(1);
		}
		//END
		//IDENTIFY COLOR
		start = ft_strstr(s, "color");
		start++;
		end = ft_strchr(start, ',');
		if (ft_strnstr(start, "red", end - start))
			new->color = RED;
		else if (ft_strnstr(start, "green", end - start))
			new->color = GREEN;
		else if (ft_strnstr(start, "blue", end - start))
			new->color = BLUE;
		else if (ft_strnstr(start, "yellow", end - start))
			new->color = YELLOW;
		else if (ft_strnstr(start, "purple", end - start))
			new->color = PURPLE;
		else
		{
			printf("check config file for mistakes\n");
			exit(1);
		}
		//END
		//GET SPECULAR
		start = ft_strstr(s, "specular");
		if ((str = ft_strextract(start, ':', ',')) == NULL)
			str = ft_strextract(start, ':', '}');
		new->specular = ft_atof(str);
		free(str);
		start = ft_strstr(s, "reflection");
		if ((str = ft_strextract(start, ':', ',')) == NULL)
			str = ft_strextract(start, ':', '}');
		new->reflection = ft_atof(str);
		free(str);
		//END
		//GET CENTER
		start = ft_strstr(s, "center");
		str = ft_strextract(start, '[', ']');
		extract_coord(str, &new->center);
		free(str);
		//END
		//GET DIRECTION
		start = ft_strstr(s, "direction");
		str = ft_strextract(start, '[', ']');
		extract_coord(str, &new->unit);
		free(str);
		//END
		//GET RADIUS
		if (new->figure != PLANE && new->figure != CONE)
		{
			start = ft_strstr(s, "radius");
			if ((str = ft_strextract(start, ':', ',')) == NULL)
				str = ft_strextract(start, ':', '}');
			new->radius = ft_atof(str);
			free(str);
		}
		//END
		//GET ANGLE
		if (new->figure == CONE)
		{
			start = ft_strstr(s, "angle");
			if ((str = ft_strextract(start, ':', ',')) == NULL)
				str = ft_strextract(start, ':', '}');
			//printf("str - %s\n", str);
			new->angle = (M_PI * ft_atof(str)) / 180;
			//printf("angle - %f\n", new->angle);
			free(str);
		}
		//END
		//printf("object %d - %s\n\n", i, object);
		i++;
		s += ft_strlen(object);
		push_back_shape(head, new);
	}
}
