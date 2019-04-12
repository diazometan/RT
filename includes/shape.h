/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 18:49:50 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/12 17:47:09 by lwyl-the         ###   ########.fr       */
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
	double			specular;
	double			reflection;
	double			refract;
	double			emission;
	double			u;
	double			v;
	t_matrix		rotation;
	t_texture		*texture;
	t_texture		*tex_normal;
	t_vec3			dims;
	t_vec3			center;
	t_vec3			surface_point;
	t_vec3			unit;
	t_vec3			normal;
	double			(*gd_fun)();
	struct s_shape	*next;
}					t_shape;

void				push_back_shape(t_shape **head, t_shape *new);
void				init_shape_color(char *s, t_shape *new);
void				init_shape_function_1(t_shape *new);
void				init_spec_refl(char *s, t_shape *new);
void				init_direction(char *s, t_shape *new);
void				init_dimensions(char *s, t_shape *new);
void				init_center(char *s, t_shape *new);
void				init_refraction(char *s, t_shape *new);
void				init_function(t_shape *new);

#endif
