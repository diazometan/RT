/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcount.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 12:59:47 by rgyles            #+#    #+#             */
/*   Updated: 2018/12/04 14:06:28 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstcount(t_list *begin_list)
{
	int		count;
	t_list	*cur;

	count = 0;
	cur = begin_list;
	if (begin_list == NULL)
		return (0);
	while (cur->next != NULL)
	{
		cur = cur->next;
		count++;
	}
	return (count + 1);
}
