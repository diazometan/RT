/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 19:03:42 by rgyles            #+#    #+#             */
/*   Updated: 2018/11/30 20:53:26 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *cur;
	t_list *tmp;

	cur = *alst;
	if (cur == NULL)
		return ;
	while (cur != NULL)
	{
		tmp = cur;
		cur = cur->next;
		ft_lstdelone(&tmp, del);
	}
	*alst = NULL;
}
