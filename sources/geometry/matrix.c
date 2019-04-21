/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 11:55:32 by lwyl-the          #+#    #+#             */
/*   Updated: 2019/04/15 13:56:50 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_matrix		matrix_multiply(t_matrix a, t_matrix b)
{
	t_matrix	res;
	int			i;
	int			j;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
		{
			res.matrix[i][j] = a.matrix[i][0] * b.matrix[0][j] +
				a.matrix[i][1] * b.matrix[1][j] +
				a.matrix[i][2] * b.matrix[2][j];
		}
	}
	return (res);
}

t_matrix		x_rotation_matrix(double alpha)
{
	t_matrix	res;
	double		sin_t;
	double		cos_t;

	sin_t = sin(alpha);
	cos_t = cos(alpha);
	res = (t_matrix) {{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}};
	res.matrix[1][1] = cos_t;
	res.matrix[1][2] = -sin_t;
	res.matrix[2][1] = sin_t;
	res.matrix[2][2] = cos_t;
	return (res);
}

t_matrix		y_rotation_matrix(double beta)
{
	t_matrix	res;
	double		sin_t;
	double		cos_t;

	sin_t = sin(beta);
	cos_t = cos(beta);
	res = (t_matrix) {{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}};
	res.matrix[0][0] = cos_t;
	res.matrix[0][2] = sin_t;
	res.matrix[2][0] = -sin_t;
	res.matrix[2][2] = cos_t;
	return (res);
}

t_matrix		z_rotation_matrix(double gamma)
{
	t_matrix	res;
	double		sin_t;
	double		cos_t;

	sin_t = sin(gamma);
	cos_t = cos(gamma);
	res = (t_matrix) {{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}};
	res.matrix[0][0] = cos_t;
	res.matrix[0][1] = -sin_t;
	res.matrix[1][0] = sin_t;
	res.matrix[1][1] = cos_t;
	return (res);
}

void			vector_matrix_multiply(t_matrix m, t_vec3 *ray)
{
	t_vec3	pre;

	pre.x = ray->x;
	pre.y = ray->y;
	pre.z = ray->z;
	ray->x = pre.x * m.matrix[0][0] + pre.y * m.matrix[1][0] +
				pre.z * m.matrix[2][0];
	ray->y = pre.x * m.matrix[0][1] + pre.y * m.matrix[1][1] +
				pre.z * m.matrix[2][1];
	ray->z = pre.x * m.matrix[0][2] + pre.y * m.matrix[1][2] +
				pre.z * m.matrix[2][2];
}
