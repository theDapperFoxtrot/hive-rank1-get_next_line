/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smishos <smishos@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 13:21:24 by smishos           #+#    #+#             */
/*   Updated: 2024/05/11 15:07:30 by smishos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_free_buffer(char *buffer);
char	*ft_check_for_newline(int fd, char *buffer);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer;

	// Check if BUFFER_SIZE is valid and if file descriptor is valid
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	// Allocate memory for buffer
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	// Check if buffer is NULL
	if (!buffer)
		ft_free_buffer(buffer); // Free buffer if it is NULL
	ft_check_for_newline(fd, buffer); // Check for newline in buffer
	line = ft_strdup(buffer);
	//add to the buffer until we reach a newline
	while (!ft_strchr(buffer, '\n'))
	{
		if (!ft_check_for_newline(fd, buffer))
			break;
		line = ft_strjoin(line, buffer);
	}
	return (line);
}

void	ft_free_buffer(char *buffer)
{
	// Free buffer and set it to NULL
	if (buffer)
	{
		free(buffer);
		buffer = NULL;
	}
}
// Check for newline in buffer
char	*ft_check_for_newline(int fd, char *buffer)
{
	int		bytes_read;
	char	*temp;
	// Read from file descriptor into buffer
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	// Check if read was successful
	if (bytes_read == -1)
	{
		ft_free_buffer(buffer);
		return (NULL);
	}
	// Set null terminator at end of buffer because read does not do it and it's needed because buffer is not initialized
	buffer[bytes_read] = '\0';
	temp = ft_strchr(buffer, '\n'); // Check for newline in buffer
	// If newline is found, set null terminator at newline and return buffer
	if (temp)
	{
		*temp = '\0'; // Set null terminator at newline
		return (buffer); // Return buffer
	}
	return (NULL); // Return NULL if newline is not found
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
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