/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 12:48:04 by rgyles            #+#    #+#             */
/*   Updated: 2018/12/04 12:48:06 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	ch;
	unsigned char	*tmp_src;
	unsigned char	*tmp_dst;

	tmp_src = (unsigned char *)src;
	tmp_dst = (unsigned char *)dst;
	ch = (unsigned char)c;
	while (n > 0)
	{
		*tmp_dst = *tmp_src;
		if (*tmp_src == ch)
			return (tmp_dst + 1);
		tmp_dst++;
		tmp_src++;
		n--;
	}
	return (NULL);
}
