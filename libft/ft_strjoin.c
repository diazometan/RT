/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 12:59:42 by rgyles            #+#    #+#             */
/*   Updated: 2019/01/29 14:42:32 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		lens1;
	int		lens2;
	char	*str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	lens1 = ft_strlen((char*)s1);
	lens2 = ft_strlen((char*)s2);
	if (!(str = (char *)malloc(sizeof(*str) * (lens1 + lens2 + 1))))
		return (NULL);
	while (lens1-- > 0)
	{
		str[i++] = *s1;
		s1++;
	}
	while (lens2-- > 0)
	{
		str[i++] = *s2;
		s2++;
	}
	str[i] = '\0';
	return (str);
}
