/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 17:30:08 by rgyles            #+#    #+#             */
/*   Updated: 2018/11/30 10:37:46 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	ch;
	unsigned char	*tmp_s;

	ch = (unsigned char)c;
	tmp_s = (unsigned char *)s;
	while (n > 0)
	{
		if (*tmp_s == ch)
			return ((char*)s);
		tmp_s++;
		s++;
		n--;
	}
	return (NULL);
}
