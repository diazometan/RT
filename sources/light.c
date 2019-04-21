/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 13:03:37 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/21 13:57:39 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double	get_specular(t_rt *rt, t_light *light,
						t_vec3 *dir, double shape_specular)
{
	double	r_length;
	double	specular;
	double	ray_sum;
	double	light_t_norm;
	t_vec3	ray;

	specular = 0.0;
	light_t_norm = vec3_dot(&light->ray, &rt->normal);
	ray.x = 2 * rt->normal.x * light_t_norm - light->ray.x;
	ray.y = 2 * rt->normal.y * light_t_norm - light->ray.y;
	ray.z = 2 * rt->normal.z * light_t_norm - light->ray.z;
	r_length = vec3_length(&ray);
	ray.x *= -dir->x;
	ray.y *= -dir->y;
	ray.z *= -dir->z;
	ray_sum = ray.x + ray.y + ray.z;
	if (ray_sum > 0)
		specular = light->intensity * pow(ray_sum /
			(r_length * vec3_length(dir)), shape_specular);
	return (specular);
}

static double	get_spot_light(t_vec3 *dir, t_rt *rt,
						t_light *light, double specular)
{
	double	l_length;
	double	light_sum;
	double	light_t_norm;
	double	cosi;
	double	tmp;

	light_sum = 0.0;
	tmp = 0.0;
	vec3_subtract(&rt->source_point, &light->center, &light->ray);
	vec3_normalize(&light->ray, vec3_length(&light->ray));
	cosi = vec3_dot(&light->ray, &light->dir);
	if (!(cosi > cos(light->angle)))
		return (light_sum);
	vec3_subtract(&light->center, &rt->source_point, &light->ray);
	light_t_norm = vec3_dot(&light->ray, &rt->normal);
	if ((light_t_norm) > 0)
	{
		l_length = vec3_length(&light->ray);
		if ((tmp = shadow(&rt->source_point,
				light->ray, rt->head_shapes, l_length)) == 0)
			return (0);
		cosi = (cosi - cos(light->angle)) / (1.0 - cos(light->angle));
		light_sum = cosi * light->intensity * (light_t_norm / l_length);
		// if (specular > 0)
		// 	light_sum += get_specular(rt, light, dir, specular);
	}
	return (light_sum * tmp);
}

static double	get_point_light(t_vec3 *dir, t_rt *rt,
					t_light *light, double specular)
{
	double	l_length;
	double	light_sum;
	double	light_t_norm;
	double	tmp;

	light_sum = 0.0;
	tmp = 0.0;
	vec3_subtract(&light->center, &rt->source_point, &light->ray);
	light_t_norm = vec3_dot(&light->ray, &rt->normal);
	if ((light_t_norm) > 0)
	{
		l_length = vec3_length(&light->ray);
		if ((tmp = shadow(&rt->source_point,
				light->ray, rt->head_shapes, l_length)) == 0)
			return (0);
		light_sum = light->intensity * light_t_norm / (l_length);
		// if (specular > 0)
		// 	light_sum += get_specular(rt, light, dir, specular);
	}
	return (light_sum * tmp);
}

static double	get_dir_light(t_vec3 *dir, t_rt *rt,
					t_light *light, double specular)
{
	double	l_length;
	double	light_sum;
	double	light_t_norm;
	double	tmp;

	tmp = 0.0;
	light_sum = 0.0;
	light_t_norm = vec3_dot(&light->ray, &rt->normal);
	if ((light_t_norm) > 0)
	{
		l_length = vec3_length(&light->ray);
		if ((tmp = shadow(&rt->source_point,
				light->ray, rt->head_shapes, l_length)) == 0)
			return (0);
		light_sum = light->intensity * (light_t_norm / l_length);
		// if (specular > 0)
		// 	light_sum += get_specular(rt, light, dir, specular);
	}
	return (light_sum * tmp);
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
				light_sum += get_point_light(dir, rt, head, shape->specular);
			else if (head->type == SPOT)
				light_sum += get_spot_light(dir, rt, head, shape->specular);
			else if (head->type == DIRECTIONAL)
				light_sum += get_dir_light(dir, rt, head, shape->specular);
			else if (head->type == AMBIENT)
				light_sum += head->intensity;
		}
		head = head->next;
	}
	return (light_sum);
}
