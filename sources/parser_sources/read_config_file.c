/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_config_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 10:24:29 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/22 19:58:49 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static size_t	count_letters(char *file)
{
	char	c;
	size_t	len;

	len = 0;
	while ((c = *file) != '\0')
	{
		if (c != ' ' && c != '\t' && c != '\n')
			++len;
		++file;
	}
	return (len);
}

static char		*remove_white_spaces(char *file)
{
	size_t	i;
	size_t	len;
	char	c;
	char	*p;
	char	*config;

	i = 0;
	len = count_letters(file);
	if ((config = ft_strnew(len)) == NULL)
	{
		free(file);
		return (NULL);
	}
	p = file;
	while ((c = *file) != '\0')
	{
		if (c != ' ' && c != '\t' && c != '\n')
			config[i++] = c;
		++file;
	}
	free(p);
	return (config);
}

char			*get_file(int fd)
{
	int		check;
	char	*line;
	char	*file;
	char	*tmp;

	if ((file = ft_strnew(1)) == NULL)
		return (NULL);
	while ((check = get_next_line(fd, &line)))
	{
		if (check == -1 || (tmp = ft_strjoin(file, line)) == NULL)
		{
			free(file);
			return (NULL);
		}
		free(line);
		free(file);
		file = tmp;
	}
	if (ft_strlen(file) == 0)
	{
		ft_putendl(E_FILE);
		free(file);
		return (NULL);
	}
	return (remove_white_spaces(file));
}
