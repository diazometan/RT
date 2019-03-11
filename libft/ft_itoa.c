/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 13:40:43 by rgyles            #+#    #+#             */
/*   Updated: 2018/12/12 20:36:35 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_length(long n)
{
	int len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	while (n > 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static int	power(int n)
{
	int p;

	p = 1;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		p *= 10;
		n--;
	}
	return (p);
}

static void	ft_write(long nb, char **number, int len)
{
	int i;

	i = 0;
	if (nb < 0)
	{
		nb *= -1;
		*(*number + i) = '-';
		i++;
		len--;
	}
	while (len > 0)
	{
		*(*number + i) = '0' + (nb / power(len - 1) % 10);
		len--;
		i++;
	}
	*(*number + i) = '\0';
}

char		*ft_itoa(int n)
{
	int		len;
	long	nb;
	char	*number;

	nb = n;
	len = ft_length(nb);
	if (!(number = (char *)malloc(sizeof(*number) * (len + 1))))
		return (NULL);
	ft_write(nb, &number, len);
	return (number);
}
