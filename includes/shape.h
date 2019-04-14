/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 18:42:32 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/14 18:49:32 by rgyles           ###   ########.fr       */
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
	double			specular;
	double			reflection;
	double			refract;
	double			emission;
	double			u;
	double			v;
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

#endif
