/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 11:55:32 by lwyl-the          #+#    #+#             */
/*   Updated: 2019/04/01 18:19:13 by lwyl-the         ###   ########.fr       */
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

//t_matrix		matrix_multiply(t_matrix a, t_matrix b)
//{
	//t_matrix	matrix_m;
//
	//matrix_m.xx = a.xx * b.xx + a.xy * b.yx + a.xz * b.zx;
	//matrix_m.xy = a.xx * b.xy + a.xy * b.yy + a.xz * b.zy;
	//matrix_m.xz = a.xx * b.xz + a.xy * b.yz + a.xz * b.zz;
	//matrix_m.yx = a.yx * b.xx + a.yy * b.yx + a.yz * b.zx;
	//matrix_m.yy = a.yx * b.xy + a.yy * b.yy + a.yz * b.zy;
	//matrix_m.yz = a.yx * b.xz + a.yy * b.yz + a.yz * b.zz;
	//matrix_m.zx = a.zx * b.xx + a.zy * b.yx + a.zz * b.zx;
	//matrix_m.zy = a.zx * b.xy + a.zy * b.yy + a.zz * b.zy;
	//matrix_m.xx = a.zx * b.xz + a.zy * b.yz + a.zz * b.zz;
	//return (matrix_m);
//}

t_matrix		x_rotation_matrix(double alpha)
{
	//t_matrix	matrix;
	t_matrix	res;
	double		sin_t;
	double		cos_t;

	sin_t = sin(alpha);
	cos_t = cos(alpha);
	res = (t_matrix) {{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}};
	//matrix.xx = 1.0;
	//matrix.xy = 0.0;
	//matrix.xz = 0.0;
	//matrix.yx = 0.0;
	//matrix.yy = cos_t;
	//matrix.yz = -sin_t;
	//matrix.zx = 0.0;
	//matrix.zy = sin_t;
	//matrix.zz = cos_t;
	res.matrix[1][1] = cos_t;
	res.matrix[2][1] = sin_t;
	res.matrix[1][2] = -sin_t;
	res.matrix[2][2] = cos_t;
	return (res);
	//return (matrix);
}

t_matrix		y_rotation_matrix(double beta)
{
	//t_matrix	matrix;
	t_matrix	res;
	double		sin_t;
	double		cos_t;

	sin_t = sin(beta);
	cos_t = cos(beta);
	res = (t_matrix) {{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}};
	//matrix.xx = cos_t;
	//matrix.xy = 0.0;
	//matrix.xz = sin_t;
	//matrix.yx = 0.0;
	//matrix.yy = 1.0;
	//matrix.yz = 0.0;
	//matrix.zx = -sin_t;
	//matrix.zy = 0.0;
	//matrix.zz = cos_t;
	res.matrix[0][0] = cos_t;
	res.matrix[0][2] = sin_t;
	res.matrix[2][0] = -sin_t;
	res.matrix[2][2] = cos_t;
	return (res);
	//return (matrix);
}

void			vector_matrix_multiply(t_matrix m, t_coord *ray)
{
	t_coord	pre;

	pre.x = ray->x;
	pre.y = ray->y;
	pre.z = ray->z;
	//ray->x = pre.x * matrix.xx + pre.y * matrix.yx + pre.z * matrix.zx;
	//ray->y = pre.x * matrix.xy + pre.y * matrix.yy + pre.z * matrix.zy;
	//ray->z = pre.x * matrix.xz + pre.y * matrix.yz + pre.z * matrix.zz;
	ray->x = pre.x * m.matrix[0][0] + pre.y * m.matrix[1][0] +
				pre.z * m.matrix[2][0];
	ray->y = pre.x * m.matrix[0][1] + pre.y * m.matrix[1][1] +
				pre.z * m.matrix[2][1];
	ray->z = pre.x * m.matrix[0][2] + pre.y * m.matrix[1][2] +
				pre.z * m.matrix[2][2];
}
