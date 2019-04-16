/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 18:26:16 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/16 18:59:56 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			init_function_texture(t_shape *new)
{
	if (new->figure == PLANE)
		new->map_texture = &plane_texture;
	else if (new->figure == SPHERE || new->figure == ELIPSIOD)
		new->map_texture = &sphere_texture;
	else if (new->figure == CYLINDER)
		new->map_texture = &cylinder_texture;
	else if (new->figure == CONE)
		new->map_texture = &cone_texture;
	else if (new->figure == TORUS)
		new->map_texture = &torus_texture;
	else if (new->figure == BOX || new->figure == FRACTAL)
		new->map_texture = &box_texture;
	//else if (new->figure == CAPSULE)
//		//new->map_texture = &gd_capsule;
}

void			init_function(t_shape *new)
{
	if (new->figure == PLANE)
		new->gd_fun = &gd_plane;
	else if (new->figure == SPHERE)
		new->gd_fun = &gd_sphere;
	else if (new->figure == CYLINDER)
		new->gd_fun = &gd_cylinder;
	else if (new->figure == CONE)
		new->gd_fun = &gd_cone;
	else if (new->figure == TORUS)
		new->gd_fun = &gd_torus;
	else if (new->figure == BOX)
		new->gd_fun = &gd_box;
	else if (new->figure == CAPSULE)
		new->gd_fun = &gd_capsule;
	else if (new->figure == ELIPSIOD)
		new->gd_fun = &gd_elispoid;
	else if (new->figure == FRACTAL)
		new->gd_fun = &gd_fractal;
}
