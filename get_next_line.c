/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 08:41:55 by tcali             #+#    #+#             */
/*   Updated: 2025/01/21 15:30:44 by tcali            ###   ########.fr       */
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

	buffer = malloc(1);
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	printf("Start reading file...\n");
	while (list->bytes_read > 0 && ft_strchr(buffer, '\n') == NULL)
	{
		printf("Entering while loop... (bytes_read: %d, list->buf: %s)\n", list->bytes_read, list->buf);
		temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!temp)
			return (NULL);
		list->bytes_read = read(fd, temp, BUFFER_SIZE);
		if (list->bytes_read < 0)
			return (free(temp), free(buffer), NULL);
		temp[list->bytes_read] = '\0';
		buffer = ft_join_free(buffer, temp);
		printf("\nread_file : buffer = [%s]\n", buffer);
	}
	return (buffer);
}

void	ft_parse_line(t_list *list)
{
	char	*new_line_index;
	t_list	*new_node;

	if (!list || !list->buf)
		return ;
	new_line_index = ft_strchr(list->buf, '\n');
	if (!new_line_index)
		return ;
	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	new_node->buf = ft_strdup(new_line_index + 1);
	if (!new_node->buf)
		return (free(new_node));
	*new_line_index = '\0';
	new_node->next = NULL;
	list->next = new_node;
}

char	*get_next_line(int fd)
{
	static t_list	list;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	list.bytes_read = 1;
	list.buf = read_file(fd, &list);
	if (list.buf == NULL)
		return (NULL);
	line = ft_strdup(list.buf);
	if (line == NULL)
		return (free(list.buf), NULL);
	ft_parse_line(&list);
	return (line);
}
