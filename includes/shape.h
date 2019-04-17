/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 18:42:32 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/17 13:50:05 by rgyles           ###   ########.fr       */
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
	double			refraction;
	double			emission;
	double			u;
	double			v;
	t_vec3			color;
	t_vec3			dims;
	t_vec3			center;
	t_vec3			surface_point;
	t_vec3			unit;
	t_vec3			normal;
	double			(*gd_fun)();
	t_vec3			(*map_texture)();
	t_matrix		rotation;
	t_texture		*texture;
	t_texture		*tex_normal;
	struct s_shape	*next;
}					t_shape;

int					identify_shape(char *start);
void				identify_color(char *s, t_vec3 *color);
void				init_center(char *s, t_vec3 *center);
void				init_direction(char *s, t_vec3 *unit, t_matrix *rotation);
void				init_dimensions(char *s, int figure, t_vec3 *dims);
void				init_reflection(char *s, double *reflection);
void				init_refraction(char *s, double *refraction);
void				init_specular(char *s, double *specular);
void				init_function(t_shape *new);
void				init_function_texture(t_shape *new);
void				init_texture(char *object, t_shape *new, t_texture **head_textures);
void				init_texture_map(char *object, t_shape *shape, t_texture **head_textures);

int					strcequ(char const *s1, char const *s2, int c);
char				*get_end(char *s, int c_s, int c_e);
double				get_double(char *s, int c);
void				get_vector(char *s, t_vec3 *vec);

#endif
