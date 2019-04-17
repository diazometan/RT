/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 10:16:14 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/17 09:27:53 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	ft_strcequ(char const *s1, char const *s2, int c)
{
	char	ch1;
	char	ch2;

	if (s1 == NULL || s2 == NULL)
		return (0);
	while (((ch1 = *s1) != '\0') && ((ch2 = *s2) != '\0') && (c != ch1))
	{
		if (ch1 != ch2)
			return (0);
		++s1;
		++s2;
	}
	return (1);
}

char	*get_end(char *s, int c_s, int c_e)
{
	int		pair;
	char	c;

	pair = 0;
	while ((c = *s) != '\1')
	{
		if (c == c_s)
			++pair;
		else if (c == c_e)
		{
			if (pair == 0)
				return (s);
			--pair;
		}
		++s;
	}
	return (NULL);
}
