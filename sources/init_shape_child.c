/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shape_child.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:31:39 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/04/12 14:32:01 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			init_shape_child(t_shape *new, t_shape *shape1, t_shape *shape2)
{
	new->f_is_in_group = 0;
	new->shape1 = shape1;
	new->shape2 = shape2;
	new->f_is_group = (new->shape1 != NULL && new->shape2 != NULL);
	if (new->shape1 != NULL)
		new->shape1->f_is_in_group = 1;
	if (new->shape2 != NULL)
		new->shape2->f_is_in_group = 1;
}
