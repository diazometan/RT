/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 10:40:49 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/02 19:27:09 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	vec2_length(t_vec2 *vector)
{
	return (sqrt(pow(vector->x, 2) + pow(vector->y, 2)));
}

double	vec2_dot(t_vec2 *a, t_vec2 *b)
{
	return (a->x * b->x + a->y * b->y);
}
