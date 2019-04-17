/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 18:42:32 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/17 15:56:04 by lwyl-the         ###   ########.fr       */
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

typedef struct		s_hsv_color
{
	unsigned char	h;
	unsigned char	s;
	unsigned char	v;
}					t_hsv_color;

typedef struct		s_rgb_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}					t_rgb_color;

typedef struct		s_shape
{
	int				figure;
	double			specular;
	double			reflection;
	double			refract;
	double			emission;
	t_matrix		rotation;
	t_texture		*texture;
	t_texture		*tex_normal;
	t_vec3			color;
	t_vec3			dims;
	t_vec3			center;
	t_vec3			surface_point;
	t_vec3			unit;
	t_vec3			normal;
	double			(*gd_fun)();
	t_vec3			(*map_texture)();
	struct s_shape	*next;
	int				id;
	int				f_is_group;
	int				f_is_in_group;
	struct s_shape	*shape1;
	struct s_shape	*shape2;
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
void				init_function_texture(t_shape *new);
int					init_texture(char *object, t_shape *new, t_texture **head_textures);
int					init_texture_map(char *object, t_shape *shape, t_texture **head_textures);
void				init_shape_child(t_shape *new, t_shape *shape1, t_shape *shape2);
void				init_id(char *s, t_shape *new);

#endif
