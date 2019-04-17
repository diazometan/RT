/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_summ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:30:34 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/04/17 17:48:50 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	shape_summ(t_vec3 *p, t_shape *shape)
{
	if(shape->group & 2)
		return (shape->gd_fun(p, shape->child_one, shape->child_two));
	else
		return (shape->gd_fun(p, shape));
}
