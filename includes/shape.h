/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 18:49:50 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/20 10:05:57 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_H
# define SHAPE_H

typedef struct		s_shape
{
	int				figure;
	int				color;
	double			angle;
	double			radius;
	double			specular;
	double			reflection;
	double			h;
	double			refract;
	t_coord			abc[3];
	t_coord			triangle[3];
	t_coord			center;
	t_coord			surface_point;
	t_coord			unit;
	t_coord			normal;
	struct s_shape	*next;
}					t_shape;

void				push_back_shape(t_shape **head, t_shape *new);
void				init_shape_color(char *s, t_shape *new);
void				init_spec_refl(char *s, t_shape *new);
void				init_direction(char *s, t_shape *new);
void				init_radius(char *s, t_shape *new);
void				init_angle(char *s, t_shape *new);
void				init_height(char *s, t_shape *new);
void				init_triangle(char *s, t_shape *new);
void				init_center(char *s, t_shape *new);
void				init_refraction(char *s, t_shape *new);

#endif
