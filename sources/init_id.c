/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_id.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:31:24 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/04/12 14:32:26 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			init_id(char *s, t_shape *new)
{
	char	*start;
	char	*str;

	start = ft_strstr(s, "id");
	if (start == NULL)
	{
		ft_putendl(M_ID PFCF);
		exit(1);
	}
	if ((str = ft_strextract(start, ':', ',')) == NULL)
		str = ft_strextract(start, ':', '\0');
	new->id = ft_atof(str);
	free(str);
}
