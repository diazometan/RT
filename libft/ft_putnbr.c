/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 14:03:38 by rgyles            #+#    #+#             */
/*   Updated: 2018/11/28 15:52:26 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_number(int i)
{
	if (i / 10 == 0)
		ft_putchar('0' + i);
	else
	{
		print_number(i / 10);
		i %= 10;
		print_number(i);
	}
}

void		ft_putnbr(int n)
{
	if (n == -2147483648)
	{
		ft_putstr("-2147483648");
		return ;
	}
	if (n < 0)
	{
		ft_putchar('-');
		print_number(n * (-1));
	}
	else
		print_number(n);
}
