/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 09:54:24 by rgyles            #+#    #+#             */
/*   Updated: 2018/12/09 17:01:18 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_limit_check(int flag)
{
	if (flag)
		return (1);
	else
		return (-1);
}

int			ft_atoi(const char *str)
{
	size_t	i;
	int		flag;

	flag = 0;
	i = 0;
	while (*str == '\n' || *str == '\t' || *str == ' '
			|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-')
		flag++;
	if (*str == '+' || *str == '-')
		str++;
	while (*str != '\0' && *str >= '0' && *str <= '9')
	{
		if ((i = i * 10 + (*str - 48)) > 9223372036854775807)
			return (ft_limit_check(flag));
		str++;
	}
	if (flag)
		return (-i);
	else
		return (i);
}
