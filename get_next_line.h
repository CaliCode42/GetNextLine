/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 08:43:47 by tcali             #+#    #+#             */
/*   Updated: 2025/01/21 13:17:39 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

typedef struct s_list
{
	char			*buf;
	int				bytes_read;
	struct s_list	*next;
}				t_list;

char	*get_next_line(int fd);

char	*ft_join_free(char *buffer, char *buf);
int		ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *source);
char	*ft_strjoin(char *s1, char *s2);

#endif