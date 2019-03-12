/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 13:03:37 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/12 20:44:36 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double	get_reflection(t_shape *shape, t_light *light,
											double light_t_norm)
{
	double	r_length;
	double	light_sum;
	double	ray_sum;
	t_coord	ray;

	light_sum = 0.0;
	ray.x = 2 * shape->normal.x * (light_t_norm) - light->ray.x;
	ray.y = 2 * shape->normal.y * (light_t_norm) - light->ray.y;
	ray.z = 2 * shape->normal.z * (light_t_norm) - light->ray.z;
	r_length = vector_length(&ray);
	ray.x *= -shape->ray.x;
	ray.y *= -shape->ray.y;
	ray.z *= -shape->ray.z;
	ray_sum = ray.x + ray.y + ray.z;
	if (ray_sum > 0)
	{
		shape->l_ray = vector_length(&shape->ray);
		light_sum = light->intensity * pow(ray_sum /
			(r_length * shape->l_ray), shape->specular);
	}
	return (light_sum);
}

static double	get_point_light(t_shape *shape, t_light *light)
{
	double	l_length;
	double	light_sum;
	double	light_t_norm;

	light_sum = 0.0;
	coord_add_subtract(&light->point, &shape->surface_point, &light->ray, 1);
	l_length = vector_length(&light->ray);
	light_t_norm = dot_product(&light->ray, &shape->normal);
	if ((light_t_norm) > 0)
		light_sum = light->intensity * (light_t_norm / l_length);
	if (shape->specular > 0)
		light_sum += get_reflection(shape, light, light_t_norm);
	return (light_sum);
}

static double	get_directional_light(t_shape *shape, t_light *light)
{
	double	l_length;
	double	light_sum;
	double	light_t_norm;

	light_sum = 0.0;
	light->ray.x = light->point.x;
	light->ray.y = light->point.y;
	light->ray.z = light->point.z;
	l_length = vector_length(&light->ray);
	light_t_norm = dot_product(&light->ray, &shape->normal);
	if ((light_t_norm) > 0)
		light_sum = light->intensity * (light_t_norm / l_length);
	if (shape->specular > 0)
		light_sum += get_reflection(shape, light, light_t_norm);
	return (light_sum);
}

double			get_light(t_shape *shape, t_rt *rt)
{
	double	light_sum;
	t_light	*head;

	light_sum = 0.0;
	head = rt->head_light;
	while (head != NULL)
	{
		if (head->intensity != 0.0)
		{
			if (head->type == 1 && check_shadow(shape, head, rt))
				light_sum += get_point_light(shape, head);
			else if (head->type == 2 && check_shadow(shape, head, rt))
				light_sum += get_directional_light(shape, head);
			else if (head->type == 3)
				light_sum += head->intensity;
		}
		head = head->next;
	}
	return (light_sum);
}
