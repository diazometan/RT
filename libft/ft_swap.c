/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swapuni.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 10:50:00 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/20 11:10:15 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swap(void *a, void *b)
{
	size_t	size_a;
	size_t	size_b;
	void	*tmp_b;

	size_a = sizeof(a);
	size_b = sizeof(a);
	if (size_a != size_b || (!(tmp_b = malloc(size_a))))
	{
		ft_putstr("error occured in ft_swap");
		exit(0);
	}
	ft_memmove(tmp_b, b, size_a);
	ft_memmove(b, a, size_a);
	ft_memmove(a, tmp_b, size_a);
	free(tmp_b);
}
