/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 12:07:43 by rgyles            #+#    #+#             */
/*   Updated: 2018/11/29 16:11:51 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char *area;

	if (!(area = (char *)malloc(sizeof(*area) * size)))
		return (NULL);
	ft_bzero(area, size);
	return (area);
}
