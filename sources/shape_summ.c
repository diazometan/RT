/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_summ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:30:34 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/04/12 14:30:47 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	shape_summ(t_vec3 *p, t_shape *shape)
{
	if(!shape->f_is_group)
		return (shape->gd_fun(p, shape));
	else
		return (shape->gd_fun(p, shape->shape1, shape->shape2));
}
