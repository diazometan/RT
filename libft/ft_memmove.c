/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 16:41:14 by rgyles            #+#    #+#             */
/*   Updated: 2018/11/30 09:45:06 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*tmp_dst;
	unsigned char	*tmp_src;

	tmp_dst = (unsigned char*)dst;
	tmp_src = (unsigned char*)src;
	if (tmp_dst > tmp_src)
		while (len--)
			*(tmp_dst + len) = *(tmp_src + len);
	else if (tmp_dst != tmp_src)
		while (len--)
			*tmp_dst++ = *tmp_src++;
	return (dst);
}
