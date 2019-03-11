/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 14:34:56 by rgyles            #+#    #+#             */
/*   Updated: 2018/11/30 20:55:41 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int			flag;
	char		ch;
	const char	*tmp;

	flag = 0;
	tmp = s;
	ch = (char)c;
	while (*tmp != '\0')
	{
		if (ch == *tmp)
		{
			flag = 1;
			s = tmp;
		}
		tmp++;
	}
	if (flag)
		return ((char*)s);
	else if (c == '\0')
		return ((char*)tmp);
	return (NULL);
}
