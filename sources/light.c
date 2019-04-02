/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 13:03:37 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/02 18:00:20 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double	get_specular(t_shape *shape, t_light *light,
								t_vec3 *dir, double light_t_norm)
{
	double	r_length;
	double	new_r_length;
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
	{
		new_r_length = vec3_length(dir);
		specular = light->intensity * pow(ray_sum /
			(r_length * new_r_length), shape->specular);
	}
	return (specular);
}

static double	get_point_light(t_vec3 *dir, t_shape *shape, t_light *light, t_shape *head_shape)
{
	double	l_length;
	double	light_sum;
	double	light_t_norm;

	light_sum = 0.0;
	vec3_subtract(&light->point, &shape->surface_point, &light->ray);
	light_t_norm = vec3_dot(&light->ray, &shape->normal);
	if ((light_t_norm) > 0)
	{
		l_length = vec3_length(&light->ray);
		vec3_normalize(&light->ray, l_length);
		if (shadow(&shape->surface_point, &light->ray, head_shape, l_length))
			return (0);
		//printf("a - %f b - %f c - %f\n", light->intensity, light_t_norm, l_length);
		light_sum = light->intensity * (light_t_norm / l_length);
		if (shape->specular > 0)
			light_sum += get_specular(shape, light, dir, light_t_norm);
	}
	//printf("light - %f\n", light_sum);
	return (light_sum);
}

static double	get_directional_light(t_vec3 *dir, t_shape *shape, t_light *light, t_shape *head_shape)
{
	double	l_length;
	double	light_sum;
	double	light_t_norm;

	light_sum = 0.0;
	light_t_norm = vec3_dot(&light->ray, &shape->normal);
	if ((light_t_norm) > 0)
	{
		l_length = vec3_length(&light->ray);
		vec3_normalize(&light->ray, l_length);
		if (shadow(&shape->surface_point, &light->ray, head_shape, l_length))
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
			else if (head->type == DIRECTIONAL)
				light_sum += get_directional_light(dir, shape, head, rt->head_shapes);
			else if (head->type == AMBIENT)
				light_sum += head->intensity;
		}
		head = head->next;
	}
	//printf("light - %f\n", light_sum);
	return (light_sum);
}

/*double			get_light(t_shape *shape, t_rt *rt, t_coord *dir)
{
	double	light_sum;
	t_light	*head;

	light_sum = 0.0;
	head = rt->head_light;
	while (head != NULL)
	{
		if (head->intensity > 0.0)
		{
			if (head->type == 1 && check_shadow(shape, head, rt))
				light_sum += get_point_light(shape, head, dir);
			else if (head->type == 2 && check_shadow(shape, head, rt))
				light_sum += get_directional_light(shape, head, dir);
			else if (head->type == 3)
				light_sum += head->intensity;
		}
		head = head->next;
	}
	return (light_sum);
}*/
