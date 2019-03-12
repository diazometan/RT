/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strextract.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 11:19:49 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/12 11:22:47 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_end(char *s, int c_s, int c_e)
{
	while (s != NULL && *s != '\0' && *s != c_e)
	{
		if (*s == c_s)
		{
			s = get_end(s + 1, c_s, c_e);
			if (s == NULL)
				return (NULL);
		}
		s++;
	}
	if (s == NULL || *s == '\0')
		return (NULL);
	return (s);
}

char		*ft_strextract(const char *s, int c_s, int c_e)
{
	size_t	len;
	char	*start;
	char	*end;
	char	*str;

	if ((start = ft_strchr(s, c_s)) == NULL)
		return (NULL);
	if ((end = get_end(start + 1, c_s, c_e)) == NULL)
		return (NULL);
	len = end - start - 1;
	str = ft_strsub(start, 1, len);
	return (str);
}
