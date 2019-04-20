/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_parse_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 15:11:45 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/20 13:49:53 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		init_direction(char *s, t_vec3 *unit, t_matrix *rotation)
{
	if ((s = ft_strstr(s, "\"direction\"")) == NULL || *(s + 11) != ':')
	{
		ft_putendl(M_DIR);
		exit(1);
	}
	get_vector(s + 12, unit);
	if (rotation != NULL)
	{
		vec3_scalar(unit, M_PI / 180.0);
		*rotation = matrix_multiply(inverse_x_rotate(unit->x),
			matrix_multiply(inverse_y_rotate(unit->y),
			inverse_z_rotate(unit->z)));
	}
}

void		init_center(char *s, t_vec3 *center)
{
	if ((s = ft_strstr(s, "\"center\"")) == NULL || *(s + 8) != ':')
	{
		ft_putendl(M_CENTER);
		exit(1);
	}
	get_vector(s + 9, center);
}

void		identify_color(char *s, t_vec3 *color)
{
	if ((s = ft_strstr(s, "\"color\"")) == NULL || *(s + 7) != ':')
	{
		ft_putendl(M_COLOR);
		exit(1);
	}
	get_vector(s + 8, color);
	if (color->x < 0 || color->x > 255 || color->y < 0
		|| color->y > 255 || color->z < 0 || color->z > 255)
	{
		ft_putendl(U_COLOR);
		exit(1);
	}
}
