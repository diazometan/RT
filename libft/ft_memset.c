/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 13:56:16 by rgyles            #+#    #+#             */
/*   Updated: 2018/11/28 16:10:10 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char	*tmp;

	tmp = (char *)b;
	while (len > 0)
	{
		*tmp = (unsigned char)c;
		len--;
		tmp++;
	}
	return (b);
}
