/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddlast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 12:17:32 by rgyles            #+#    #+#             */
/*   Updated: 2018/12/09 13:47:05 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstaddlast(t_list **alst, t_list *new)
{
	t_list *cur;

	cur = *alst;
	if (*alst == NULL)
	{
		*alst = new;
		return ;
	}
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = new;
}
