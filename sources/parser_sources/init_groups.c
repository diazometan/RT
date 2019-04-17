/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_groups.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:04:26 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/17 17:18:38 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_shape	*find_child(char *s, char *child, t_shape **head_shapes)
{
	int		id;
	t_shape	*head;

	head = *head_shapes;
	if ((s = ft_strstr(s, child)) == NULL || *(s + 3) != ':')
	{
		ft_putendl(M_CHILD);
		exit(1);
	}
	else if ((id = get_double(s + 13, ',')) < 0)
	{
		ft_putendl(U_CHILD);
		exit(1);
	}
	while (head != NULL)
	{
		if (head->id == id)
			return (head);
		head = head->next;
	}
	ft_putendl(V_CHILD);
	exit(1);
	//return (NULL);
}

void	init_id(char *s, int *id)
{
	if ((s = ft_strstr(s, "\"id\"")) == NULL || *(s + 3) != ':')
	{
		ft_putendl(M_ID);
		exit(1);
	}
	else if ((*id = get_double(s + 13, ',')) < 0)
	{
		ft_putendl(U_ID);
		exit(1);
	}
}
