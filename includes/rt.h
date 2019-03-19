/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 19:14:44 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/18 18:54:33 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "libft.h"
# include "vector.h"
# include "constants.h"
# include "shape.h"
# include "SDL.h"
# include <math.h>
# include <limits.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct		s_sdl
{
	SDL_Window		*win;
	SDL_Surface		*surf;
	int				*img_data;
}					t_sdl;

typedef struct		s_light
{
	int				type;
	double			intensity;
	t_coord			ray;
	t_coord			point;
	struct s_light	*next;
}					t_light;

typedef struct		s_rt
{
	int				win_width;
	int				win_height;
	int				p_division;
	int				depth;
	double			pixel_step;
	double			leha_help;
	double			t_closest;
	t_coord			angle;
	t_coord			camera;
	t_coord			*source_point;
	t_shape			*head_shapes;
	t_light			*head_light;
}					t_rt;

typedef struct		s_vectors
{
	double			max;
	double			min;
	t_coord			orig;
	t_coord			*dir;
}					t_vectors;

typedef struct		s_coef
{
	double			a;
	double			b;
	double			scalar_a;
	double			scalar_b;
	double			discriminant;
}					t_coef;

typedef struct		s_matrix
{
	double			matrix[3][3];
}					t_matrix;

int					init_config(char *file, t_rt *rt);
void				extract_coord(char *str, t_coord *coord);
void				init_lighting(char *s, t_light **head);
void				init_shapes(char *s, t_shape **head);
void				init_physics(char *s, t_rt *rt);
void				create_caps(t_rt *rt);
void				free_args(t_shape *shape, t_light *light);

void				create_img(t_rt *rt, t_sdl *sdl);
int					check_intersection(t_coord *ray, t_shape *shape, t_rt *rt, int flag);

double				sphere_intersection(t_shape *shape, t_vectors *vectors);
void				get_normal_sphere(t_shape *shape);

double				cylinder_intersection(t_shape *shape, t_vectors *vectors, t_rt *rt);
void				get_normal_cylinder(t_shape *shape);

double				cone_intersection(t_shape *shape, t_vectors *vectors, t_rt *rt);
void				get_normal_cone(t_shape *shape, double alpha);

double				plane_intersection(t_shape *shape, t_vectors *vectors, t_rt *rt);
double				ray_plane_intersection(t_vectors *vectors, t_shape *shape);
void				get_normal_plane(t_shape *shape, t_coord *dir);

double				disk_intersection(t_shape *shape, t_vectors *vectors, t_rt *rt);
double				triangle_intersection(t_shape *shape, t_vectors *vectors, t_rt *rt);

int					trace_ray(t_coord *ray, t_rt *rt, int depth);
int					get_color(t_shape *first, t_rt *rt, t_coord *dir, int depth);
int					reflection(t_coord *dir, t_shape *shape, t_rt *rt, int depth);
int					check_shadow(t_shape *source_shape,
									t_light *light, t_rt *rt);
double				get_light(t_shape *shape, t_rt *rt, t_coord *dir);

void				get_intersection_point(t_coord *source, t_coord *ray, double t, t_coord *p);

void				event_handler(t_rt *rt, t_sdl *sdl);

t_matrix			matrix_multiply(t_matrix a, t_matrix b);
t_matrix			x_rotation_matrix(double alpha);
t_matrix			y_rotation_matrix(double beta);
void				vector_matrix_multiply(t_matrix m, t_coord *ray);

#endif
