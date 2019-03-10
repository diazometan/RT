/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 12:59:01 by rgyles            #+#    #+#             */
/*   Updated: 2018/12/04 17:44:22 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_swap_int(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static int		ft_partition(int *array, int i, int j)
{
	int pivot;

	pivot = array[(j + i) / 2];
	while (i <= j)
	{
		while (array[i] < pivot)
			i++;
		while (array[j] > pivot)
			j--;
		if (i <= j)
			ft_swap_int(&array[i++], &array[j--]);
	}
	return (i);
}

void			ft_qsort(int *array, int start, int end)
{
	int border;

	if (start >= end || array == NULL)
		return ;
	border = ft_partition(array, start, end);
	ft_qsort(array, start, border - 1);
	ft_qsort(array, border, end);
	return ;
}
