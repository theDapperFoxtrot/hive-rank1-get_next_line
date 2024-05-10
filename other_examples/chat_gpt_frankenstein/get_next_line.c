/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smishos <smishos@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 10:36:58 by smishos           #+#    #+#             */
/*   Updated: 2024/05/09 12:29:26 by smishos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*new_str;

	len = ft_strlen(s);
	new_str = (char *)ft_calloc(len + 1, sizeof(char));
	if (new_str)
	{
		ft_memcpy(new_str, s, len);
	}
	return (new_str);
}

static char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*result;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = (char *)malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, s1, len1);
	ft_memcpy(result + len1, s2, len2);
	result[len1 + len2] = '\0';
	return (result);
}

static char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(&s[i]));
		i++;
	}
	if ((char)c == 0)
		return ((char *)(&s[i]));
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		buffer[BUFFER_SIZE + 1];
	char		*newline_ptr;
	char		*line;
	int			bytes_read;

	if (!remainder)
		remainder = ft_strdup("");
	while ((newline_ptr = ft_strchr(remainder, '\n')) == NULL)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		remainder = ft_strjoin(remainder, buffer);
	}
	size_t line_length = (newline_ptr) ? newline_ptr - remainder : ft_strlen(remainder);
	line = (char *)malloc((line_length + 1) * sizeof(char));
	if (!line)
		return (NULL);
	ft_memcpy(line, remainder, line_length);
	line[line_length] = '\0';
	if (newline_ptr)
		remainder = ft_strdup(newline_ptr + 1);
	else
	{
		free(remainder);
		return (NULL);
	}
	return (line);
}
