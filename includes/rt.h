/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 19:14:44 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/31 16:21:05 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "libft.h"
# include "vector.h"
# include "constants.h"
# include "SDL.h"
# include "shape.h"
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
	double			sample_step;
	double			sample_center;
	double			t_closest;
	t_coord			angle;
	t_coord			camera;
	t_coord			*source_point;
	t_shape			*head_shapes;
	t_light			*head_light;
	t_texture		*head_textures;
	SDL_Surface		*surf_bmp;
	SDL_Surface		*surf_norm;
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

int					init_config(char *file, t_rt *rt);
void				extract_coord(char *str, t_coord *coord);
void				init_lighting(char *s, t_light **head);
void				init_shapes(char *s, t_shape **head, t_texture **head_textures);
void				init_physics(char *s, t_rt *rt);
int					init_texture(char *object, t_shape *new, t_texture **head_textures);
void				create_caps(t_rt *rt);
void				free_args(t_shape *shape, t_light *light, t_texture *texture);

void				create_img(t_rt *rt, t_sdl *sdl);
int					check_intersection(t_coord *ray, t_shape *shape, t_rt *rt, int flag);

double				sphere_intersection(t_shape *shape, t_vectors *vectors);
void				get_normal_sphere(t_shape *shape);
int					sphere_texture(t_texture *texture, t_shape *shape);

double				cylinder_intersection(t_shape *shape, t_vectors *vectors, t_rt *rt);
void				get_normal_cylinder(t_shape *shape);
int					cylinder_texture(t_shape *shape, t_rt *rt);

double				cone_intersection(t_shape *shape, t_vectors *vectors, t_rt *rt);
void				get_normal_cone(t_shape *shape, double alpha);

double				plane_intersection(t_shape *shape, t_vectors *vectors, t_rt *rt);
//double				ray_plane_intersection(t_vectors *vectors, t_shape *shape);
void				get_normal_plane(t_shape *shape, t_coord *dir);
int					plane_texture(t_texture *texture, t_shape *shape);

//double				disk_intersection(t_shape *shape, t_vectors *vectors, t_rt *rt);
//double				triangle_intersection(t_shape *shape, t_vectors *vectors, t_rt *rt);

int					trace_ray(t_coord *ray, t_rt *rt); //int depth);
int					get_color(t_shape *first, t_rt *rt, t_coord *dir, int depth);
double				path_tracing(t_shape *shape, t_rt *rt, int depth);
int					reflection(t_coord *dir, t_shape *shape, t_rt *rt, int depth);
int					refraction(t_coord *dir, t_shape *shape, t_rt *rt, int depth);
int					check_shadow(t_shape *source_shape,
									t_light *light, t_rt *rt);
double				get_light(t_shape *shape, t_rt *rt, t_coord *dir);

void				get_intersection_point(t_coord *source, t_coord *ray, double t, t_coord *p);

void				event_handler(t_rt *rt, t_sdl *sdl);

#endif
