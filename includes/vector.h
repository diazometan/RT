/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 14:12:06 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/17 14:20:23 by rgyles           ###   ########.fr       */
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

void	scalar_product(t_coord *a, double number);
void	cross_product(t_coord *a, t_coord *b, t_coord *c);
double	dot_product(t_coord *a, t_coord *b);
double	vector_length(struct s_coord *vector);
void	normalize_vector(t_coord *vector, double length);
void	coord_add_subtract(t_coord *a, t_coord *b,
							t_coord *result, int flag);

#endif
