/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtammi <rtammi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:13:25 by rtammi            #+#    #+#             */
/*   Updated: 2024/05/09 16:35:09 by rtammi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*fd_next(char *buffer)
{
	int		i;
	int		j;
	char	*next;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (free_return(buffer));
	next = ft_calloc(ft_strlen(buffer) - i + 1, sizeof(char));
	if (!next)
		return (free_return(buffer));
	i++;
	while (buffer[i])
		next[j++] = buffer[i++];
	free(buffer);
	buffer = NULL;
	return (next);
}

char	*fd_line(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!buffer[i])
		return (free_return(buffer));
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
		line = ft_calloc(i + 1, sizeof(char));
	else
		line = ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*read_bytes(int fd, char *buffer, char *result)
{
	int		bytes;
	char	*temp;

	bytes = 1;
	while (bytes > 0 && !ft_strchr(result, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
			return (NULL);
		buffer[bytes] = 0;
		temp = strjoin_free(result, buffer);
		if (!temp)
		{
			free(result);
			result = NULL;
			free(buffer);
			buffer = NULL;
			return (NULL);
		}
		free(result);
		result = NULL;
		result = temp;
	}
	return (result);
}

char	*fd_file(int fd, char *result)
{
	char	*buffer;

	if (!result)
		result = ft_calloc(1, 1);
	if (!result)
		return (NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (free_return(result));
	result = read_bytes(fd, buffer, result);
	if (!result)
		return (NULL);
	free(buffer);
	buffer = NULL;
	if (ft_strlen(result) == 0)
		return (free_return(result));
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (buffer != NULL)
			free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = fd_file(fd, buffer);
	if (buffer == NULL)
		return (NULL);
	line = fd_line(buffer);
	if (line == NULL)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = fd_next(buffer);
	return (line);
}
