/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 13:03:37 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/19 18:50:08 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double	get_specular(t_shape *shape, t_light *light,
						t_vec3 *dir, double light_t_norm)
{
	double	r_length;
	double	specular;
	double	ray_sum;
	t_vec3	ray;

	specular = 0.0;
	ray.x = 2 * shape->normal.x * light_t_norm - light->ray.x;
	ray.y = 2 * shape->normal.y * light_t_norm - light->ray.y;
	ray.z = 2 * shape->normal.z * light_t_norm - light->ray.z;
	r_length = vec3_length(&ray);
	ray.x *= -dir->x;
	ray.y *= -dir->y;
	ray.z *= -dir->z;
	ray_sum = ray.x + ray.y + ray.z;
	if (ray_sum > 0)
		specular = light->intensity * pow(ray_sum /
			(r_length * vec3_length(dir)), shape->specular);
	return (specular);
}

static double	get_spot_light(t_vec3 *dir, t_shape *shape,
						t_light *light, t_shape *head_shape) //изменить угол раствора
{
	double	l_length;
	double	light_sum;
	double	light_t_norm;
	double	cosi;
	double	sini;

	light_sum = 0.0;
	vec3_subtract(&shape->surface_point, &light->center, &light->ray);
	vec3_normalize(&light->ray, vec3_length(&light->ray));
	cosi = vec3_dot(&light->ray, &light->dir);
	sini = sqrt(1 - cosi * cosi);
	if (!(cosi > cos(light->angle * M_PI / 180)))
		return (light_sum);
	vec3_subtract(&light->center, &shape->surface_point, &light->ray);
	light_t_norm = vec3_dot(&light->ray, &shape->normal);
	if ((light_t_norm) > 0)
	{
		l_length = vec3_length(&light->ray);
		if (shadow(&shape->surface_point,
				light->ray, head_shape, l_length) == 0)
			return (0);
		cosi = (cosi - cos(light->angle * M_PI / 180)) / (1.0 - cos(light->angle * M_PI / 180));
		light_sum = cosi * light->intensity * (light_t_norm / l_length);
		if (shape->specular > 0)
			light_sum += get_specular(shape, light, dir, light_t_norm);
	}
	return (light_sum);
}

static double	get_point_light(t_vec3 *dir, t_shape *shape,
					t_light *light, t_shape *head_shape)
{
	double	l_length;
	double	light_sum;
	double	light_t_norm;
	double	tmp = 0.0;

	light_sum = 0.0;
	vec3_subtract(&light->center, &shape->surface_point, &light->ray);
	light_t_norm = vec3_dot(&light->ray, &shape->normal);
	if ((light_t_norm) > 0)
	{
		l_length = vec3_length(&light->ray);
		if ((tmp = shadow(&shape->surface_point,
				light->ray, head_shape, l_length)) == 0)
			return (0);
		light_sum = light->intensity * light_t_norm / (l_length);
		if (shape->specular > 0)
			light_sum += get_specular(shape, light, dir, light_t_norm);
	}
	return (light_sum * tmp);
}

static double	get_dir_light(t_vec3 *dir, t_shape *shape,
					t_light *light, t_shape *head_shape)
{
	double	l_length;
	double	light_sum;
	double	light_t_norm;

	light_sum = 0.0;
	light_t_norm = vec3_dot(&light->ray, &shape->normal);
	if ((light_t_norm) > 0)
	{
		l_length = vec3_length(&light->ray);
		if (shadow(&shape->surface_point,
				light->ray, head_shape, l_length) == 0)
			return (0);
		light_sum = light->intensity * (light_t_norm / l_length);
		if (shape->specular > 0)
			light_sum += get_specular(shape, light, dir, light_t_norm);
	}
	return (light_sum);
}

double			get_light(t_vec3 *dir, t_shape *shape, t_rt *rt)
{
	double	light_sum;
	t_light	*head;

	light_sum = 0.0;
	head = rt->head_light;
	while (head != NULL)
	{
		if (head->intensity > 0.0)
		{
			if (head->type == POINT)
				light_sum += get_point_light(dir, shape, head, rt->head_shapes);
			else if (head->type == SPOT)
				light_sum += get_spot_light(dir, shape, head, rt->head_shapes);
			else if (head->type == DIRECTIONAL)
				light_sum += get_dir_light(dir, shape, head, rt->head_shapes);
			else if (head->type == AMBIENT)
				light_sum += head->intensity;
		}
		head = head->next;
	}
	return (light_sum);
}
