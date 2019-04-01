/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 14:12:06 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/01 19:03:54 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct		s_coord
{
	double			x;
	double			y;
	double			z;
}					t_coord;

typedef struct		s_matrix
{
	double			matrix[3][3];
	//double	xx;
	//double	xy;
	//double	xz;
	//double	yx;
	//double	yy;
	//double	yz;
	//double	zx;
	//double	zy;
	//double	zz;
}					t_matrix;

void	scalar_product(t_coord *a, double number);
void	cross_product(t_coord *a, t_coord *b, t_coord *c);
double	dot_product(t_coord *a, t_coord *b);
double	vector_length(struct s_coord *vector);
void	normalize_vector(t_coord *vector, double length);
void	coord_add_subtract(t_coord *a, t_coord *b,
							t_coord *result, int flag);

t_matrix			matrix_multiply(t_matrix a, t_matrix b);
t_matrix			x_rotation_matrix(double alpha);
t_matrix			y_rotation_matrix(double beta);
void				vector_matrix_multiply(t_matrix m, t_coord *ray);

t_matrix inverse_z_rotate(double alpha);
t_matrix inverse_y_rotate(double gamma);
t_matrix inverse_x_rotate(double beta);

#endif
