/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 13:14:39 by rgyles            #+#    #+#             */
/*   Updated: 2019/01/20 16:50:52 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int count;

	count = 0;
	while (*s != '\0')
	{
		while (*s == c)
			s++;
		if (*s == '\0')
			return (count);
		count++;
		while (*s != c && *s != '\0')
			s++;
	}
	return (count);
}

static int	ft_count_letters(char *s, char c)
{
	int count;

	count = 0;
	while (*s != '\0')
	{
		while (*s == c)
			s++;
		while (*s != c && *s != '\0')
		{
			count++;
			s++;
		}
		return (count);
	}
	return (count);
}

static char	*ft_write_word(char **s, char c)
{
	int		i;
	int		count;
	char	*word;

	i = 0;
	count = ft_count_letters(*s, c);
	if (!(word = (char *)malloc(sizeof(*word) * (count + 1))))
		return (NULL);
	while (i < count)
	{
		word[i] = *(*s);
		i++;
		(*s)++;
	}
	word[i] = '\0';
	return (word);
}

static void	ft_free(char ***array, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		free(*(array[i]));
		*(array[i]) = NULL;
		i++;
	}
	free(*array);
	*array = NULL;
}

char		**ft_strsplit(char const *s, char c)
{
	int		i;
	int		count;
	char	*str;
	char	**array;

	if (s == NULL)
		return (NULL);
	i = 0;
	str = (char *)s;
	count = ft_count_words(str, c);
	if (!(array = (char **)malloc(sizeof(*array) * (count + 1))))
		return (NULL);
	while (i < count)
	{
		while (*str == c || *str == '\0')
			str++;
		if ((array[i] = ft_write_word(&str, c)) == NULL)
		{
			ft_free(&array, i);
			return (NULL);
		}
		i++;
	}
	array[i] = 0;
	return (array);
}
