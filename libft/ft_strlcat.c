/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 12:33:54 by rgyles            #+#    #+#             */
/*   Updated: 2018/12/04 14:53:05 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	int		count;
	size_t	case1;
	size_t	case2;

	count = size - ft_strlen(dest) - 1;
	case1 = size + ft_strlen(src);
	case2 = ft_strlen(dest) + ft_strlen(src);
	if (count < 0)
		return (case1);
	ft_strncat(dest, src, count);
	return (case2);
}
