/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 14:49:20 by rgyles            #+#    #+#             */
/*   Updated: 2018/11/30 10:36:40 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *sub_str)
{
	const char *head;
	const char *temp_find;

	if (*sub_str == '\0')
		return ((char*)str);
	while (*str != '\0')
	{
		temp_find = sub_str;
		if (*str == *temp_find)
		{
			head = str;
			while (*head == *temp_find && *temp_find != '\0' && *head != '\0')
			{
				head++;
				temp_find++;
			}
			if (*temp_find == '\0')
				return ((char*)str);
		}
		str++;
	}
	return (NULL);
}
