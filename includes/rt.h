/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 19:14:44 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/22 20:29:37 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "libft.h"
# include "vector.h"
# include "constants.h"
# include <SDL2/SDL.h>
# include <SDL_image.h>
# include <SDL_ttf.h>
# include "kiss_sdl.h"
# include "shape.h"
# include "ui.h"
# include <math.h>
# include <limits.h>
# include <fcntl.h>
# include <stdio.h>
# include <time.h>
# include <pthread.h>

typedef struct		s_sdl
{
	SDL_Window		*win;
	SDL_Surface		*surf;
	int				*pro_data;
	int				*img_data;
}					t_sdl;

typedef struct		s_light
{
	int				type;
	double			intensity;
	double			angle;
	t_vec3			center;
	t_vec3			dir;
	struct s_light	*next;
}					t_light;

typedef struct		s_trace
{
	double			max_distance;
	double			min_distance;
	double			epsilon;
	double			t;
	double			d;
}					t_trace;

typedef struct		s_cone_texture
{
	t_vec3			angle;
	t_vec3			unit1;
	t_vec3			r;
}					t_cone_texture;

typedef	enum
{
	STANDART,
	INVERSE_ONE,
	INVERSE_TWO,
	GREY,
	CARTOON
}	t_color_scheme;

typedef struct		s_rt
{
	int				win_width;
	int				win_height;
	int				total_pixels;
	int				p_division;
	int				depth;
	int				sample;
	int				threads;
	int				count;
	int				effect_type;
	double			sample_step;
	double			sample_center;
	double			t_closest;
	double			g_noise[NOISE_HEIGHT][NOISE_WIDTH];
	t_vec3			angle;
	t_vec3			camera;
	t_vec3			source_point;
	t_vec3			normal;
	t_vec3			color;
	t_vec3			light_ray;
	t_shape			*head_shapes;
	t_light			*head_light;
	t_texture		*head_textures;
	t_color_scheme	color_scheme;
}					t_rt;

typedef struct		s_pthread
{
	t_rt			*rt;
	t_sdl			*sdl;
	int				x;
	int				y;
	int				size;
	int				index;
}					t_pthread;

typedef struct		s_body_pthread
{
	int				size;
	pthread_t		*tid;
	t_pthread		*blocks;
	t_rt			*new_rts;
}					t_body_pthread;

void				progress_bar(double progress, t_rt *rt, t_sdl *sdl);

char				*get_file(int fd);
int					init_config(char *file, t_rt *rt);
char				*init_shapes(char *s, t_shape **head,
									t_texture **head_textures);
char				*init_lighting(char *s, t_light **head);
int					init_physics(char *s, t_rt *rt);
void				free_args(t_shape *shape, t_light *light,
									t_texture *texture);
void				exit_programm(t_rt *rt, t_sdl *sdl);
void				*check_memory(void *new);

void				create_img(t_rt *rt, t_sdl *sdl);
int					trace_ray(t_vec3 *dir, t_rt *rt, int depth);

double				gd_sphere(t_vec3 *p, t_shape *shape);
double				gd_plane(t_vec3 *p, t_shape *shape);
double				gd_cylinder(t_vec3 *p, t_shape *shape);
double				gd_infinity_cylinder(t_vec3 *p, t_shape *shape);
double				gd_cone(t_vec3 *p, t_shape *shape);
double				gd_infinity_cone(t_vec3 *p, t_shape *shape);
double				gd_torus(t_vec3 *p, t_shape *shape);
double				gd_capsule(t_vec3 *p, t_shape *shape);
double				gd_box(t_vec3 *p, t_shape *shape);
double				gd_elispoid(t_vec3 *p, t_shape *shape);
double				gd_fractal(t_vec3 *p, t_shape *shape);
double				gd_half_space(t_vec3 *p, t_shape *shape);

double				intersect(double dist_a, double dist_b);
double				unite(double dist_a, double dist_b);
double				difference(double dist_a, double dist_b);
double				blend(double dist_a, double dist_b);
double				mix(double dist_a, double dist_b);
double				shape_summ(t_vec3 *p, t_shape *shape);

int					get_color(t_vec3 *dir, t_shape *shape, t_rt *rt, int depth);
double				get_light(t_vec3 *dir, t_shape *shape, t_rt *rt);
void				get_normal(t_vec3 *surface_point,
								t_vec3 *normal, t_shape *shape);
double				shadow(t_vec3 orig, t_vec3 dir,
								t_shape *head_shapes, double max_distance);
int					refraction(t_vec3 *dir, t_shape *shape,
								t_rt *rt, int depth);
int					reflection(t_vec3 *dir, t_rt *rt, int depth);
int					transperency(t_vec3 *dir, t_rt *rt, int depth);

int					emission(t_shape *shape, t_rt *rt, int depth);

void				event_handler(t_rt *rt, t_sdl *sdl);
void				window_resized(t_rt *rt, t_sdl *sdl, SDL_Event *event);

void				create_normal_system(t_rt *rt, t_shape *shape);

t_vec3				get_texture_color(t_texture *texture, int xy[2],
								double uv[2], t_rt *rt);
void				move_texture(double *u, double *v, double delta_uv[2]);
t_vec3				sphere_texture(t_texture *texture,
								t_shape *shape, t_rt *rt);
t_vec3				plane_texture(t_texture *texture, t_shape *shape, t_rt *rt);
t_vec3				cylinder_texture(t_texture *texture,
								t_shape *shape, t_rt *rt);
t_vec3				cone_texture(t_texture *texture, t_shape *shape, t_rt *rt);
t_vec3				torus_texture(t_texture *texture, t_shape *shape, t_rt *rt);
t_vec3				box_texture(t_texture *texture, t_shape *shape, t_rt *rt);

double				turbulence(t_rt *rt, double x, double y, double size);
void				generate_noise(t_rt *rt);
double				smooth_noise(t_rt *rt, double x, double y);
t_vec3				noise(t_rt *rt, double x, double y);
t_vec3				wood(t_rt *rt, int x, int y);
t_vec3				marble(t_rt *rt, int x, int y);
t_vec3				chess_board(t_rt *rt, int x, int y);

void				set_color(t_rt *rt, int rgb_m[3], double light);
void				set_color_cartoon(t_rt *rt, int rgb_m[3], double light);
void				set_color_invers(t_rt *rt, int rgb_m[3], double light);
void				set_color_grey(t_rt *rt, int rgb_m[3], double light);
void				set_color_invers_hsv(t_rt *rt, int rgb_m[3], double light);
int					reflect_color(int color, int reflected_color,
									double reflection);
int					trans_color(int color, int reflected_color,
									double reflection);

t_hsv_color			rgb_to_hsv(t_rgb_color rgb);
t_rgb_color			hsv_to_rgb(t_hsv_color hsv);

void				push_back_light(t_light **head, t_light *new);
int					ui_main(t_rt *rt, t_sdl *sdl);
void				dirent_read(t_rtui *ui);
int					init_rt(t_rt *rt, char *config_file);
int					kiss_error(char *mes);
void				ui_init(t_rtui *ui);
int					kiss_light(t_rt *rt, t_sdl *sdl);
void				button_events_main(t_rtui *ui, t_rt *rt, t_sdl *sdl);
int					kiss_ambient(t_rt *rt, t_sdl *sdl);
int					kiss_saving(t_sdl *sdl);

void				create_pthread(t_rt *rt, t_sdl *sdl);
void				*create_img_pthread(void *data);
t_pthread			init_t_pthread(t_rt *rt, t_sdl *sdl, int x[2], int y[2]);

#endif
