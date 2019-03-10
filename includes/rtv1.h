/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 21:12:39 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/07 18:56:20 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "../libft/libft.h"
# include "../minilibx_macos/mlx.h"
# include <math.h>
# include <limits.h>
# include <fcntl.h>
# include <stdio.h>

# define WIN_WIDTH 600
# define WIN_HEIGHT 600
# define WIN_WIDTH_HALF WIN_WIDTH / 2
# define WIN_HEIGHT_HALF WIN_HEIGHT / 2
# define PLANE 1
# define SPHERE 2
# define CYLINDER 3
# define CONE 4

# define KEYBOARD_UP 126
# define KEYBOARD_DOWN 125
# define KEYBOARD_RIGHT 124
# define KEYBOARD_LEFT 123
# define SPACE 49
# define ESC 53
# define KEYBOARD_W 13
# define KEYBOARD_S 1
# define KEYBOARD_A 0
# define KEYBOARD_D 2
# define KEYBOARD_R 15
# define KEYBOARD_CTRL 256

typedef struct		s_img
{
	void			*img_ptr;
	int				*img_data;
	int				bpp;
	int				size_line;
	int				endian;
}					t_img;

typedef struct		s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_img			img;
}					t_mlx;

typedef struct		s_coord
{
	double			x;
	double			y;
	double			z;
}					t_coord;

typedef struct		s_shape
{
	int				figure;
	int				color;
	double			angle;
	double			radius;
	double			reflection;
	double			l_ray;
	t_coord			center;
	t_coord			ray;
	t_coord			surface_point;
	t_coord			unit;
	t_coord			normal;
	struct s_shape	*next;
}					t_shape;

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
	double			alpha;
	double			beta;
	double			t_closest;
	t_shape			*head_shapes;
	t_light			*head_light;
	t_coord			camera;
	t_coord			canvas;
	t_mlx			mlx;
}					t_rt;

typedef struct		s_ray
{
	double			max;
	double			min;
	t_coord			a;
	t_coord			b;
}					t_ray;

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

t_shape				*get_shapes(char *file_name);
int					check_shape(t_shape *shape, char **line);
t_light				*get_light_sources(char *file_name, t_rt *rt);
void				init_camera(char *file_name, t_rt *rt);
void				free_args(t_shape *shape, t_light *light);

void				create_img(t_rt *rt);
int					check_intersection(t_shape *shape, t_rt *rt);

double				sphere_intersection(t_shape *shape, t_ray *ray);
void				get_normal_sphere(t_shape *shape);

double				cylinder_intersection(t_shape *shape, t_ray *ray);
void				get_normal_cylinder(t_shape *shape);

double				cone_intersection(t_shape *shape, t_ray *ray);
void				get_normal_cone(t_shape *shape, double alpha);

double				plane_intersection(t_shape *shape, t_ray *ray);
void				get_normal_plane(t_shape *shape);

int					get_color(t_shape *first, t_rt *rt);
int					check_shadow(t_shape *source_shape,
									t_light *light, t_rt *rt);
double				get_light(t_shape *shape, t_rt *rt);

void				scalar_product(t_coord *a, double number);
double				dot_product(t_coord *a, t_coord *b);
double				vector_length(struct s_coord *vector);
void				normalize_vector(t_coord *vector, double length);
void				coord_add_subtract(t_coord *a, t_coord *b,
										t_coord *result, int flag);

int					key_press(int key, t_rt *rt);
int					close_win(t_rt *rt);

t_matrix			matrix_multiply(t_matrix a, t_matrix b);
t_matrix			x_rotation_matrix(double alpha);
t_matrix			y_rotation_matrix(double beta);
void				vector_matrix_multiply(t_matrix m, t_shape *shape);

#endif
