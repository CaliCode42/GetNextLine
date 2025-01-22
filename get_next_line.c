/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 08:41:55 by tcali             #+#    #+#             */
/*   Updated: 2025/01/22 12:57:11 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

char	*read_file(int fd, t_list *list)
{
	char	*temp;
	char	*buffer;

	buffer = malloc(sizeof(char) * 1);
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	while (list->bytes_read > 0 && ft_strchr(buffer, '\n') == NULL)
	{
		temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!temp)
			return (free(buffer), NULL);
		list->bytes_read = read(fd, temp, BUFFER_SIZE);
		if (list->bytes_read < 0)
			return (free(temp), free(buffer), NULL);
		temp[list->bytes_read] = '\0';
		buffer = ft_join_free(buffer, temp);
		if (!buffer)
			return (NULL);
	}
	return (buffer);
}

void	ft_parse_line(t_list *list)
{
	char	*new_line_index;

	if (!list || !list->buf)
		return ;
	list->new_line = NULL;
	new_line_index = ft_strchr(list->buf, '\n');
	if (new_line_index)
	{
		list->new_line = ft_strdup(new_line_index + 1);
		if (!list->new_line)
			return ;
		*new_line_index = '\0';
	}
	else if (ft_strchr(list->buf, '\n') && list->buf)
		list->new_line = NULL;
	if (list->line != NULL)
		list->line = ft_join_free(list->line, list->buf);
	else
		list->line = ft_strdup(list->buf);
	if (!list->line && list->new_line)
		return (free(list->new_line));
}

char	*get_next_line(int fd)
{
	static t_list	list;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	list.bytes_read = 1;
	list.buf = read_file(fd, &list);
	if (list.buf == NULL)
		return (NULL);
	list.line = NULL;
	if (list.new_line)
	{
		list.line = ft_strdup(list.new_line);
		if (!list.line)
			return (free(list.new_line), NULL);
		free(list.new_line);
	}
	ft_parse_line(&list);
	if (list.bytes_read == 0 && !list.new_line && (!list.line || !*list.line))
		return (NULL);
	if (list.line == NULL && list.buf)
		return (free(list.buf), NULL);
	return (list.line);
}
