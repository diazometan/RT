/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 14:12:06 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/02 18:33:38 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct		s_vec3
{
	double			x;
	double			y;
	double			z;
}					t_vec3;

typedef struct		s_vec2
{
	double			x;
	double			y;
}					t_vec2;

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

t_matrix			matrix_multiply(t_matrix a, t_matrix b);
t_matrix			x_rotation_matrix(double alpha);
t_matrix			y_rotation_matrix(double beta);
void				vector_matrix_multiply(t_matrix m, t_vec3 *ray);

//NEW
void				vec3_add(t_vec3 *a, t_vec3 *b, t_vec3 *result);
void				vec3_subtract(t_vec3 *a, t_vec3 *b, t_vec3 *result);
double				vec3_length(t_vec3 *vector);
double				vec3_dot(t_vec3 *a, t_vec3 *b);
void				vec3_cross(t_vec3 *a, t_vec3 *b, t_vec3 *c);
void				vec3_scalar(t_vec3 *a, double number);
void				vec3_normalize(t_vec3 *vector, double length);
void				get_intersection_point(t_vec3 *source, t_vec3 *ray, double t, t_vec3 *p);

double				vec2_length(t_vec2 *vector);

t_matrix			inverse_z_rotate(double alpha);
t_matrix			inverse_y_rotate(double gamma);
t_matrix			inverse_x_rotate(double beta);
//END

#endif
