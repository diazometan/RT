/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 18:53:04 by rgyles            #+#    #+#             */
/*   Updated: 2018/11/30 09:52:59 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t len)
{
	size_t index;

	index = 0;
	while (len > 0 && src[index] != '\0')
	{
		dest[index] = src[index];
		index++;
		len--;
	}
	while (len > 0)
	{
		dest[index] = '\0';
		index++;
		len--;
	}
	return (dest);
}
