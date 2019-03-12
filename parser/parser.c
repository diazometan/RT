/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 10:34:45 by rgyles            #+#    #+#             */
/*   Updated: 2019/03/12 11:23:01 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "libft.h"

char	*get_file(int fd)
{
	int		error;
	char	*line;
	char	*file;
	char	*tmp;

	file = ft_strnew(1);
	while ((error = get_next_line(fd, &line)) > 0)
	{
		tmp = ft_strjoin(file, ft_strtrim(line));	
		free(file);
		file = tmp;
	}
	if (error == -1)
	{
		printf("gnl error occured\n");
		exit(1);
	}
	if (ft_strlen(file) == 0)
	{
		printf("empty file\n");
		exit(1);
	}
	return (file);
}

void	get_objects(const char *s)
{
	int		i;
	char	*object;

	i = 1;
	while ((object = ft_strextract(s, '{', '}')) != NULL)
	{
		printf("object %d - %s\n\n", i, object);
		i++;
		s += ft_strlen(object);
	}
}

void	get_lighting(const char *s)
{
	int		i;
	char	*start;
	char	*object;

	i = 1;
	while ((object = ft_strextract(s, '{', '}')) != NULL)
	{
		printf("light %d - %s\n\n", i, object);
		start = ft_strstr(s, "type");
		start = ft_strchr(start, ':');
		printf("type - %s\n\n", ft_strextract(start, '"', '"'));
		i++;
		s += ft_strlen(object);
	}
}

int		get_field(char *file)
{
	char	*str;
	char	*start;

	if ((start = ft_strstr(file, "objects")) == NULL)
		return (-1);
	str = ft_strextract(start, '[', ']');
	printf("\nobjects - %s\n\n", str);
	get_objects(str);
	if ((start = ft_strstr(file, "lighting")) == NULL)
		return (-1);
	str = ft_strextract(start, '[', ']');
	printf("light - %s\n\n", str);
	get_lighting(str);
	if ((start = ft_strstr(file, "camera")) == NULL)
		return (-1);
	str = ft_strextract(start, '{', '}');
	printf("camera - %s\n\n", str);
	return (5);
}

int		main(void)
{
	int		fd;
	char	*file;

	fd = open("test.json", O_RDONLY);
	file = get_file(fd);
	printf("%s\n", file);
	printf("result - %d\n", get_field(file));
	free(file);
	close(fd);
	return (0);
}
