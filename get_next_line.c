/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:29:40 by tcali             #+#    #+#             */
/*   Updated: 2025/01/10 17:54:53 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"

char	*ft_join_free(char *str, char *buffer)
{
	char	*tmp;

	tmp = ft_strjoin(str, buffer);
	free(str);
	return (tmp);
}

char	*read_file(int fd, char *str, t_buf *line)
{
	int	found_newline;

	found_newline = 0;
	if (!str)
		str = ft_calloc(1, 1);
	line->buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	line->bytes_read = 1;
	while (line->bytes_read > 0 && found_newline == 0)
	{
		line->bytes_read = read(fd, line->buffer, BUFFER_SIZE);
		if (line->bytes_read == -1)
		{
			free (str);
			free (line->buffer);
			return (NULL);
		}
		line->buffer[line->bytes_read] = 0;
		str = ft_join_free(str, line->buffer);
		if (ft_present(line->buffer, '\n'))
			found_newline = 1;
	}
	free(line->buffer);
	return (str);
}

char	*ft_parse_line(char *buf)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!buf)
		return (NULL);
	printf("avant ft_parse_line :\nbuf = [%s]\n", buf);
	while (buf[i] && buf[i] != '\n')
		i++;
	printf("ft_parse_line après while :\nbuf = [%s]\n", buf);
	line = ft_calloc(i + 2, sizeof(char));
	while (j < i)
	{
		line[j] = buf[j];
		j++;
	}
	printf("ft_parse_line après 2e while :\nbuf = [%s]\n", buf);
	if (buf[i] == '\n' || buf[i] == '\0')
		line[j] = '\n';
	printf("ft_parse_line fin de ft :\nbuf = [%s]\n", buf);
	return (line);
}

char	*ft_new_line(char *buf)
{
	int		i;
	int		j;
	char	*new_line;

	i = 0;
	j = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (!buf[i])
	{
		free(buf);
		return (NULL);
	}
	new_line = ft_calloc(ft_strlen(buf) - i + 1, sizeof(char));
	i++;
	while (buf[i])
		new_line[j++] = buf[i++];
	free(buf);
	printf("après ft_new_line :\nbuf = [%s]\n", new_line);
	return (new_line);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	t_buf		line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buf = read_file(fd, buf, &line);
	if (!buf)
		return (NULL);
	line.line = ft_parse_line(buf);
	buf = ft_new_line(buf);
	return (line.line);
}
