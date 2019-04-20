/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 10:16:14 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/20 13:50:35 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		strcequ(char *s1, char *s2, int c)
{
	char	ch1;
	char	ch2;

	if (s1 == NULL || s2 == NULL)
		return (0);
	ch1 = *s1++;
	ch2 = *s2++;
	while (ch1 != '\0' && ch2 != '\0' && c != ch1)
	{
		if (ch1 != ch2)
			return (0);
		ch1 = *s1++;
		ch2 = *s2++;
	}
	return (1);
}

char	*get_end(char *s, int c_s, int c_e)
{
	int		pair;
	char	c;

	pair = 0;
	while ((c = *s) != '\0')
	{
		if (c == c_s && c_s != '"')
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

char	*str_extract(char *s, int c_s, int c_e)
{
	char	*end;
	size_t	len;

	if (*s != c_s)
		return (NULL);
	end = get_end(s + 1, c_s, c_e);
	len = end - s - 1;
	return (ft_strsub(s, 1, len));
}

void	init_box_radius(char *s, double *b_radius)
{
	if ((s = ft_strstr(s, "\"radius\"")) == NULL || *(s + 8) != ':')
	{
		ft_putendl(M_BRADIUS);
		exit(1);
	}
	if ((*b_radius = get_double(s + 9, ',')) < 0)
	{
		ft_putendl(U_BRADIUS);
		exit(1);
	}
}

void	init_view_angle(char *s, double *angle)
{
	if ((s = ft_strstr(s, "\"view_angle\"")) == NULL || *(s + 12) != ':')
	{
		ft_putendl(M_VANGLE);
		exit(1);
	}
	if ((*angle = get_double(s + 13, ',')) < 0 || *angle > 90)
	{
		ft_putendl(U_VANGLE);
		exit(1);
	}
}
