/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:10:07 by rgyles            #+#    #+#             */
/*   Updated: 2019/01/09 19:00:29 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_letters(char *str)
{
	size_t count;

	count = 0;
	while (*str != '\n' && *str != '\0')
	{
		count++;
		str++;
	}
	return (count);
}

static t_list	*ft_elemnew(char *line)
{
	t_list *p;

	if (!line || !(p = (t_list *)malloc(sizeof(*p))))
		return (NULL);
	p->content = line;
	p->content_size = 0;
	p->next = NULL;
	return (p);
}

static t_list	*ft_create_list(char *str)
{
	char	*line;
	size_t	length;
	t_list	*head;
	t_list	*new;

	head = NULL;
	while (*str != '\0')
	{
		length = ft_count_letters(str);
		line = ft_strncpy(ft_strnew(length), str, length);
		if (!(new = ft_elemnew(line)))
			return (NULL);
		str += length;
		if (*str != '\0')
			str++;
		ft_lstaddlast(&head, new);
	}
	return (head);
}

static int		ft_get_file(const int fd, char **str)
{
	int		ret;
	char	*tmp_str;
	char	buf[BUFF_SIZE + 1];

	*str = NULL;
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (*str == NULL)
			*str = ft_strnew(1);
		buf[ret] = '\0';
		if (!(tmp_str = ft_strjoin(*str, buf)))
		{
			free(*str);
			return (-1);
		}
		free(*str);
		*str = tmp_str;
	}
	if (*str == NULL)
		return (0);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	int				flag;
	char			*str;
	t_list			*tmp;
	static t_list	*array[FD_MAX];

	if (fd < 0 || fd > FD_MAX || read(fd, NULL, 0) < 0)
		return (-1);
	flag = ft_get_file(fd, &str);
	if (flag)
	{
		array[fd] = ft_create_list(str);
		free(str);
		if (!(array[fd]))
			return (-1);
	}
	else if (flag == -1)
		return (-1);
	if (array[fd] == NULL)
		return (0);
	*line = ft_strdup(array[fd]->content);
	tmp = array[fd];
	array[fd] = array[fd]->next;
	free(tmp->content);
	free(tmp);
	return (1);
}
