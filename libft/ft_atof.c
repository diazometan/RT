/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 16:47:55 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/06 20:06:05 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	power(int num, int p)
{
	double	result;

	result = 1;
	while (p-- > 0)
		result *= num;
	return (result);
}

static double	get_fractional_part(const char *str)
{
	size_t		i;
	long double	f;
	long double	tmp;

	i = 1;
	f = 0.0;
	while (*str != '\0' && *str >= '0' && *str <= '9')
	{
		tmp = (*str - 48) / power(10.0, i++);
		f += tmp;
		str++;
	}
	return (f);
}

double			ft_atof(const char *str)
{
	int			sign;
	long double	f;

	sign = 0;
	f = 0.0;
	while (*str == '\n' || *str == '\t' || *str == ' '
			|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-')
		sign++;
	if (*str == '+' || *str == '-')
		str++;
	while (*str != '\0' && *str != '.' && *str >= '0' && *str <= '9')
	{
		f = f * 10 + (*str - 48);
		str++;
	}
	if (*str == '.')
	{
		str++;
		f += get_fractional_part(str);
	}
	if (sign)
		return (-f);
	return (f);
}
