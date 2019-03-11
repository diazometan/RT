/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 16:45:06 by rgyles            #+#    #+#             */
/*   Updated: 2018/11/30 10:39:11 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *sub_str, size_t len)
{
	size_t i;
	size_t j;
	size_t match;
	size_t len_match;

	i = 0;
	if (sub_str[i] == '\0')
		return ((char*)str);
	if (str[i] == '\0' || ft_strlen(sub_str) > len)
		return (NULL);
	while (str[i] != '\0' && len--)
	{
		j = 0;
		match = i;
		len_match = len + 1;
		while (str[match++] == sub_str[j] && sub_str[j] != '\0' && len_match--)
			j++;
		if (sub_str[j] == '\0')
			return ((char*)str + i);
		i++;
	}
	return (NULL);
}
