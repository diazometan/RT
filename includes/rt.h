/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 19:14:44 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/07 13:21:09 by rgyles           ###   ########.fr       */
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
	t_vec3			ray;
	t_vec3			point;
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
	//int				*light_array;

	t_vec3			angle;
	t_vec3			camera;
	t_vec3			*source_point;
	t_shape			*head_shapes;
	t_light			*head_light;
	t_texture		*head_textures;
	//SDL_Surface		*surf_bmp;
	//SDL_Surface		*surf_norm;
}					t_rt;

int					init_config(char *file, t_rt *rt);
void				extract_coord(char *str, t_vec3 *coord);
void				init_lighting(char *s, t_light **head);
void				init_shapes(char *s, t_shape **head, t_texture **head_textures);
void				init_physics(char *s, t_rt *rt);
int					init_texture(char *object, t_shape *new, t_texture **head_textures);
void				create_caps(t_rt *rt);
void				free_args(t_shape *shape, t_light *light, t_texture *texture);

void				create_img(t_rt *rt, t_sdl *sdl);
int					trace_ray(t_vec3 *dir, t_rt *rt, int depth);
double				gd_sphere(t_vec3 *p, t_shape *shape);
double				gd_plane(t_vec3 *p, t_shape *shape);
double				gd_cylinder(t_vec3 *p, t_shape *shape);
double				gd_cone(t_vec3 *p, t_shape *shape);
double				gd_torus(t_vec3 *p, t_shape *shape);
double				gd_capsule(t_vec3 *p, t_shape *shape);
double				gd_box(t_vec3 *p, t_shape *shape);

double				shape_one(t_vec3 *p, t_shape *shape);

double				intersect(double dist_a, double dist_b);
double				unite(double dist_a, double dist_b);
double				difference(double dist_a, double dist_b);
double				blend(double dist_a, double dist_b);
double				mix(double dist_a, double dist_b);

int					get_color(t_vec3 *dir, t_shape *shape, t_rt *rt, int depth);
double				get_light(t_vec3 *dir, t_shape *shape, t_rt *rt);
void				get_normal(t_shape *shape);
int					shadow(t_vec3 *orig, t_vec3 dir, t_shape *head_shapes, double max_distance);
int					reflection(t_vec3 *dir, t_shape *shape, t_rt *rt, int depth);
double				emission(t_shape *shape, t_rt *rt, int depth);
//int					trace_ray(t_coord *ray, t_rt *rt); //int depth);
//int					get_color(t_shape *first, t_rt *rt, t_coord *dir, int depth);
//double				path_tracing(t_shape *shape, t_rt *rt, int depth);
//int					reflection(t_coord *dir, t_shape *shape, t_rt *rt, int depth);
//int					refraction(t_coord *dir, t_shape *shape, t_rt *rt, int depth);
//int					check_shadow(t_shape *source_shape,
									//t_light *light, t_rt *rt);
//double				get_light(t_shape *shape, t_rt *rt, t_coord *dir);

//void				get_intersection_point(t_coord *source, t_coord *ray, double t, t_coord *p);

void				event_handler(t_rt *rt, t_sdl *sdl);

#endif
