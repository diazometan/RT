/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture_dimensions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 13:46:42 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/19 15:46:56 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_texture_displace(char *s, t_vec3 *t_dims)
{
	char	*str;

	if ((str = ft_strstr(s, "\"x_displace\"")) == NULL || *(str + 12) != ':')
	{
		ft_putendl(M_XDIS);
		exit(1);
	}
	if ((t_dims->x = get_double(str + 13, ',')) < 0)
	{
		ft_putendl(U_XDIS);
		exit(1);
	}
	if ((str = ft_strstr(s, "\"y_displace\"")) == NULL || *(str + 12) != ':')
	{
		ft_putendl(M_YDIS);
		exit(1);
	}
	if ((t_dims->y = get_double(str + 13, ',')) < 0)
	{
		ft_putendl(U_YDIS);
		exit(1);
	}
}

void	init_texture_division(char *s, double *texture_div)
{
	char	*str;

	if ((str = ft_strstr(s, "\"texture_div\"")) == NULL || *(str + 13) != ':')
	{
		ft_putendl(M_TDIV);
		exit(1);
	}
	if ((*texture_div = (int)get_double(str + 14, ',')) < 0)
	{
		ft_putendl(U_TDIV);
		exit(1);
	}
}
