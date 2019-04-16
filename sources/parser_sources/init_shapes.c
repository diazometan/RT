/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 18:54:37 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/16 16:46:40 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	push_back_shape(t_shape **head, t_shape *new)
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

void	init_rotation(t_shape *new)
{
	new->rotation = matrix_multiply(inverse_x_rotate(new->unit.x),
		matrix_multiply(inverse_y_rotate(new->unit.y), inverse_z_rotate(new->unit.z)));
}

void	init_fun_allocator(char *s, t_shape *new)
{
	//int	len;

	//len = ft_strchr(s, ',') - s;
	printf("\nobject in fun_allocator - %s\n", s);
	if (ft_strcequ(s, "\"shape\"", ':') == 0)
	{
		ft_putendl(M_SHAPE PFCF);
		exit(1);
	}
	//printf("identifying shape - %s\n", s + 8);
	if ((new->figure = identify_shape(s + 8)) == -1)
	{
		ft_putendl(U_SHAPE PFCF);
		exit(1);
	}
	//printf("shape id - %d\n", new->figure);
	identify_color(s, &new->color);
	//printf("color - %.2f %.2f %.2f\n", new->color.x, new->color.y, new->color.z);
	init_center(s, &new->center);
	//printf("center - %.2f %.2f %.2f\n", new->center.x, new->center.y, new->center.z);
	init_direction(s, &new->unit);
	//printf("dir - %.2f %.2f %.2f\n", new->center.x, new->center.y, new->center.z);
	init_dimensions(s, new->figure, &new->dims);
	if (new->figure == SPHERE)
		printf("radius - %f\n", new->dims.x);
	init_reflection(s, &new->reflection);
	init_refraction(s, &new->refraction);
	init_specular(s, &new->specular);
}

int		init_shapes(char *s, t_shape **head, t_texture **head_textures)
{
	//char	*start;
	char	*end;
	//char	*object;
	//int		len;
	t_shape	*new;

	(void)head_textures;
	printf("s in init shapes - %s\n", s);
	//if (*s != '{' || (end = get_end(s + 1, '{', '}')) == NULL)
		//return (1);
	while (1)
	{
		if (*s != '{' || (end = get_end(s + 1, '{', '}')) == NULL)
			return (1);
		//len = end - s;
		*end = '\0';
		new = (t_shape *)malloc(sizeof(*new));
		new->next = NULL;
		init_fun_allocator(s + 1, new);
		s = end + 1;
		//printf("new s - %s\n", s);
		if (*s == ']')
			return (0);
		else if (*s != ',')
			return (1);
		push_back_shape(head, new);
		++s;
	}
	//exit(1);
}
	//while ((object = ft_strextract(s, '{', '}')) != NULL) //need extra check - segfault when extra spaces after object
	//{
		//new = (t_shape *)malloc(sizeof(*new));
		//new->next = NULL;
		//init_shape_color(object, new);
		///*if (new->color == WHITE && new->figure == SPHERE)
			//new->emission = 1.0;
		//else*/
			//new->emission = 0.0;//extra
		//init_spec_refl(object, new);
		//init_center(object, new);
		//init_direction(object, new);
		//init_rotation(new);
		//init_dimensions(object, new);
		//init_refraction(object, new);
		//init_function(new);
		//init_function_texture(new);
		//if (init_texture(object, new, head_textures))
			//new->texture = NULL;
		//if (init_texture_map(object, new, head_textures))
			//new->tex_normal = NULL;
		//s += ft_strlen(object);
		//free(object);
		//push_back_shape(head, new);
	//}
//}
