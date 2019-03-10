/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 19:20:57 by rgyles            #+#    #+#             */
/*   Updated: 2018/12/04 19:50:18 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free_lstchain(void *content, size_t size)
{
	char *cell;

	cell = (char *)content;
	free(cell);
	size = 0;
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*cur;
	t_list	*new;
	t_list	*head;
	void	(*del)(void *, size_t);

	del = &ft_free_lstchain;
	if (lst == NULL || !(cur = ft_lstnew(NULL, 0)))
		return (NULL);
	cur = f(lst);
	head = cur;
	lst = lst->next;
	while (lst != NULL)
	{
		if (!(new = ft_lstnew(NULL, 0)))
		{
			ft_lstdel(&head, del);
			return (NULL);
		}
		new = f(lst);
		lst = lst->next;
		cur->next = new;
		cur = new;
	}
	return (head);
}
