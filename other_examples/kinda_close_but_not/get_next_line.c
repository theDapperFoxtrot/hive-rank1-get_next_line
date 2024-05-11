/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smishos <smishos@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:27:09 by smishos           #+#    #+#             */
/*   Updated: 2024/05/11 13:07:09 by smishos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static char	*ft_newline(char *buffer);
static char	*ft_strdup(const char *s);
static void	*ft_calloc(size_t count, size_t size);
static void	*ft_memcpy(void *dst, const void *src, size_t n);

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer;
	size_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
	{
		buffer = NULL;
		return (NULL);
	}
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (!bytes_read)
		return (NULL);
	buffer[bytes_read] = '\0';
	ft_newline(buffer);
	line = ft_strdup(buffer);
	buffer[0] = '\0';
	free(buffer);
	return (line);
}

static char	*ft_newline(char *buffer)
{
	char *newline_position;
	newline_position = ft_strchr(buffer, '\n');
	if (newline_position)
	{
		*newline_position = '\0';
		ft_memmove(buffer, newline_position + 1, ft_strlen(newline_position + 1) + 1);
	}
	return (newline_position);
}

static void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;

	if (!dst && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}

static void	*ft_calloc(size_t count, size_t size)
{
	size_t	total_size;
	void	*ptr;

	if (!count && !size)
		return (ft_calloc(1, 1));
	total_size = count * size;
	if (count > SIZE_MAX / size)
		return (NULL);
	ptr = malloc(total_size);
	if (!ptr)
	{
		ptr = NULL;
		return (NULL);
	}
	if (ptr)
		ft_memset(ptr, 0, total_size);
	return (ptr);
}

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
