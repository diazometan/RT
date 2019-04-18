/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_euler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 18:17:40 by lwyl-the          #+#    #+#             */
/*   Updated: 2019/04/18 12:59:08 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_matrix		inverse_z_rotate(double alpha)
{
	t_matrix	res;
	double		sin_t;
	double		cos_t;

	sin_t = sin(alpha);
	cos_t = cos(alpha);
	res = (t_matrix) {{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}};
	res.matrix[0][0] = cos_t;
	res.matrix[0][1] = -sin_t;
	res.matrix[1][0] = sin_t;
	res.matrix[1][1] = cos_t;
	return (res);
}

t_matrix		inverse_y_rotate(double gamma)
{
	t_matrix	res;
	double		sin_t;
	double		cos_t;

	sin_t = sin(gamma);
	cos_t = cos(gamma);
	res = (t_matrix) {{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}};
	res.matrix[0][0] = cos_t;
	res.matrix[0][2] = -sin_t;
	res.matrix[2][0] = sin_t;
	res.matrix[2][2] = cos_t;
	return (res);
}

t_matrix		inverse_x_rotate(double beta)
{
	t_matrix	res;
	double		sin_t;
	double		cos_t;

	sin_t = sin(beta);
	cos_t = cos(beta);
	res = (t_matrix) {{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}};
	res.matrix[1][1] = cos_t;
	res.matrix[1][2] = -sin_t;
	res.matrix[2][1] = sin_t;
	res.matrix[2][2] = cos_t;
	return (res);
}
