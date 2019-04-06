/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 18:49:50 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/06 18:11:57 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_H
# define SHAPE_H

typedef struct		s_texture
{
	char				*name;
	unsigned char		*pixel;
	SDL_Surface			*surface;
	struct s_texture	*next;
}					t_texture;

typedef struct		s_shape
{
	int				figure;
	int				color;
	//double			radius;
	double			specular;
	double			reflection;
	//double			h;
	double			refract;
	double			emission;
	t_matrix		rotation;
	t_texture		*texture;
	t_vec3			dims;
	t_vec3			center;
	t_vec3			surface_point;
	t_vec3			unit;
	t_vec3			normal;
	double			(*gd_fun)();
	struct s_shape	*next;
	int				f_is_group;
	struct s_shape	*shape1;
	struct s_shape	*shape2;
}					t_shape;

void				push_back_shape(t_shape **head, t_shape *new);
void				init_shape_color(char *s, t_shape *new);
void				init_shape_function_1(t_shape *new);
void				init_spec_refl(char *s, t_shape *new);
void				init_direction(char *s, t_shape *new);
void				init_dimensions(char *s, t_shape *new);
//void				init_radius(char *s, t_shape *new);
//void				init_angle(char *s, t_shape *new);
//void				init_height(char *s, t_shape *new);
//void				init_triangle(char *s, t_shape *new);
void				init_center(char *s, t_shape *new);
void				init_refraction(char *s, t_shape *new);
void				init_function(t_shape *new);
void				init_shape_child(t_shape *new, t_shape *shape1, t_shape *shape2);

#endif
