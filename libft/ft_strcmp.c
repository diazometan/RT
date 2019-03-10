/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 16:00:34 by rgyles            #+#    #+#             */
/*   Updated: 2018/11/30 10:06:03 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char a;
	unsigned char b;

	while (*s1 != '\0' || *s2 != '\0')
	{
		a = (unsigned char)*s1;
		b = (unsigned char)*s2;
		if (a != b)
			return (a - b);
		s1++;
		s2++;
	}
	return (0);
}
