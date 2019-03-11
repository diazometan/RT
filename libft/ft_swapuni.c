/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swapuni.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 14:42:26 by rgyles            #+#    #+#             */
/*   Updated: 2018/12/02 19:12:46 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swapuni(void *a, void *b)
{
	size_t	size;
	void	*tmp_b;

	size = sizeof(a);
	if (!(tmp_b = malloc(size)))
	{
		ft_putstr("sorting not performed: allocation failed");
		exit(0);
	}
	ft_memmove(tmp_b, b, size);
	ft_memmove(b, a, size);
	ft_memmove(a, tmp_b, size);
	free(tmp_b);
}
