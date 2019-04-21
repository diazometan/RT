/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 18:42:32 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/21 12:18:29 by lwyl-the         ###   ########.fr       */
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
	int				id;
	int				child;
	int				group;
	int				figure;
	int				effect_type;
	double			specular;
	double			reflection;
	double			refraction;
	double			transparency;
	double			b_radius;
	t_vec3			color;
	t_vec3			dims;
	t_vec3			t_dims;
	t_vec3			center;
	t_vec3			surface_point;
	t_vec3			unit;
	t_vec3			normal;
	double			(*gd_fun)();
	t_vec3			(*map_texture)();
	t_matrix		rotation;
	t_texture		*texture;
	t_texture		*tex_normal;
	struct s_shape	*child_one;
	struct s_shape	*child_two;
	struct s_shape	*next;
}					t_shape;

void				identify_object(char *s, int *figure);
void				init_id(char *s, int *id);
t_shape				*find_child(char *s, char *child, t_shape **head_shapes);
void				identify_color(char *s, t_vec3 *color);
void				init_center(char *s, t_vec3 *center);
void				init_direction(char *s, t_vec3 *unit, t_matrix *rotation);
void				init_dimensions(char *s, int figure, t_vec3 *dims);
void				init_reflection(char *s, double *reflection);
void				init_refraction(char *s, double *refraction);
void				init_transparency(char *s, double *transparency);
void				init_specular(char *s, double *specular);
void				init_function(t_shape *new);
void				init_function_texture(t_shape *new);
void				init_texture(char *object, t_shape *new, t_texture **head_textures);
int					effect_check(char *s);
void				init_texture_map(char *object, t_shape *shape, t_texture **head_textures);
void				init_groups(char *s, t_shape *new, t_shape **head);

int					strcequ(char *s1, char *s2, int c);
char				*str_extract(char *s, int c_s, int c_e);
char				*get_end(char *s, int c_s, int c_e);
double				get_double(char *s, int c);
void				get_vector(char *s, t_vec3 *vec);
void				init_box_radius(char *s, double *b_radius);
void				init_view_angle(char *s, double *angle);
void				init_texture_displace(char *s, t_vec3 *t_dims);
void				init_texture_division(char *s, double *texture_div);

#endif
