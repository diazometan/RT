/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 19:23:52 by rgyles            #+#    #+#             */
/*   Updated: 2018/11/28 15:53:05 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_number(int i, int fd)
{
	if (i / 10 == 0)
		ft_putchar_fd('0' + i, fd);
	else
	{
		print_number(i / 10, fd);
		i %= 10;
		print_number(i, fd);
	}
}

void		ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		print_number(n * (-1), fd);
	}
	else
		print_number(n, fd);
}
