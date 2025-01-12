/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:30:25 by tcali             #+#    #+#             */
/*   Updated: 2025/01/09 16:14:03 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

typedef struct s_buf
{
	char			*buffer;
	char			*line;
	int				bytes_read;
	struct s_list	*next;
}				t_buf;

char	*get_next_line(int fd);
void	*ft_calloc(size_t elementCount, size_t elementSize);
void	ft_bzero(void *s, size_t n);
size_t	ft_strlen(const char *str);
int		ft_present(const char *str, char c);
char	*ft_strjoin(char const *s1, char const *s2);

#endif