/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 10:59:17 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/16 15:46:56 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double	power(int num, int p)
{
	double	result;

	result = 1;
	while (p-- > 0)
		result *= num;
	return (result);
}

static double	get_fractional_part(const char *str, int c)
{
	char		ch;
	size_t		i;
	long double	f;

	i = 1;
	f = 0.0;
	while ((ch = *str) != '\0' && ch != c && ch >= '0' && ch <= '9')
		f += (*str++ - 48) / power(10.0, i++);
	if (ch != c && ch != '\0')
	{
		ft_putendl(U_NUM PFCF);
		exit (1);
	}
	return (f);
}

double		get_double(char *s, int c)
{
	int		sign;
	char	ch;
	long double	f;

	sign = 0;
	f = 0.0;
	if (*s == '-')
		sign++;
	if (*s == '+' || *s == '-')
		++s;
	while ((ch = *s++) != c && ch != '\0' && ch != '.'&& ch >= '0' && ch <= '9')
		f = f * 10 + (ch - 48);
	if (ch == '.')
		f += get_fractional_part(++s, c);
	else if (ch != c && ch != '\0')
	{
		ft_putendl(U_NUM PFCF);
		exit (1);
	}
	if (sign)
		return (-f);
	return (f);
}

void		get_vector(char *s, t_vec3 *vec)
{
	char	*end;

	if (*s != '[' || (end = get_end(s + 1, '[', ']')) == NULL || (*(end + 1) != ',' && *(end + 1) != '\0'))
	{
		ft_putendl(U_VEC PFCF);
		exit (1);
	}
	++s;
	vec->x = get_double(s, ',');
	s = ft_strchr(s, ',') + 1;
	vec->y = get_double(s, ',');
	s = ft_strchr(s, ',') + 1;
	vec->z = get_double(s, ']');
}
