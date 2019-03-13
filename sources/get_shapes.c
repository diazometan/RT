/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shapes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 16:16:02 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/13 20:23:02 by lwyl-the         ###   ########.fr       */
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
