/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 15:02:55 by rgyles            #+#    #+#             */
/*   Updated: 2018/12/02 17:17:24 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	int		i;
	char	*src;
	char	*new;

	i = 0;
	if (ptr == NULL && size == 0)
		new = (char *)malloc(sizeof(*new) * 1);
	else
	{
		if (!(new = (char *)malloc(sizeof(*new) * size)))
			return (NULL);
		ft_bzero(new, size);
		if (ptr == NULL)
			return (new);
		src = (char *)ptr;
		while (src[i] != '\0' && size > 0)
		{
			new[i] = src[i];
			i++;
		}
		free(ptr);
	}
	return (new);
}
