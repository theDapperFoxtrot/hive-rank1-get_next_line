/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smishos <smishos@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 13:21:24 by smishos           #+#    #+#             */
/*   Updated: 2024/05/11 16:02:31 by smishos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_to_stash(char *curr_stash, char *buffer, int fd);
char	*ret_line_clear_stash(char **curr_stash);
char	*ft_free_null(char **str);
char	*ft_substr(char const *s, unsigned int start, size_t size);

// Get next line from file descriptor
char	*get_next_line(int fd)
{
	char			*buffer;
	static char		*stash[OPEN_MAX];
// Check if file descriptor is valid and if BUFFER_SIZE is valid
	if (fd < 0 || OPEN_MAX < fd || BUFFER_SIZE <= 0)
		return (NULL);
		// Allocate memory for buffer
	buffer = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	// Check if buffer is NULL or if read fails
	if (!buffer || read(fd, 0, 0) < 0)
	{
		ft_free_null(&stash[fd]);
		return (ft_free_null(&buffer));
	}
	// Set buffer to null terminator
	buffer[0] = 0;
	// Read to stash
	stash[fd] = read_to_stash(stash[fd], buffer, fd);
	// Return line from stash
	if (!stash[fd])
		return (NULL);
	return (ret_line_clear_stash(&stash[fd]));
}

char	*read_to_stash(char *curr_stash, char *buffer, int fd)
{
	ssize_t	bytes;

	bytes = 1;
	// Read from file descriptor into buffer
	while ((!curr_stash || (curr_stash && !ft_strchr(curr_stash, '\n')))
		&& bytes > 0)
	{
		// Read from file descriptor into buffer
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes <= 0)
		{
			if (bytes == -1)
				ft_free_null(&curr_stash);
			break ;
		}
		// Set null terminator at end of buffer
		buffer[bytes] = 0;
		// Join buffer to stash
		curr_stash = ft_join(curr_stash, buffer);
	}
	// Free buffer
	free(buffer);
	return (curr_stash);
}
// Return line from stash
char	*ret_line_clear_stash(char **curr_stash)
{
	char			*tmp;
	char			*line;
	char			*pt_to_n;
	size_t			len;

	pt_to_n = ft_strchr(*curr_stash, '\n'); // Check for newline in stash
	len = pt_to_n - *curr_stash + 1; // Get length of line
	line = ft_substr(*curr_stash, 0, len);// Get line from stash
	if (!line)
		return (ft_free_null(curr_stash)); // Free stash if line is NULL
	if (!pt_to_n || !curr_stash[0][len])// If no newline or newline is at end of stash
	{
		ft_free_null(curr_stash);// Free stash
		return (line);// Return line
	}
	tmp = *curr_stash;// Set temp to stash
	*curr_stash = ft_substr(*curr_stash, len, ft_strlen(*curr_stash) - len);// Set stash to rest of stash
	if (!*curr_stash)// If stash is NULL
		*curr_stash = NULL;// Set stash to NULL
	ft_free_null(&tmp);// Free temp
	return (line);// Return line
}

char	*ft_free_null(char **str)
{
	free(*str);
	*str = NULL;
	return (*str);
}

char	*ft_substr(char const *s, unsigned int start, size_t size)
{
	char	*new;
	size_t	chr_left;

	if (start >= ft_strlen(s))// If start is greater than length of s
		return (ft_strdup(""));// Return empty string
	chr_left = ft_strlen(s + start);// Get length of s from start
	if (size > chr_left)//	If size is greater than chr_left
		size = chr_left;// Set size to chr_left
	new = (char *) malloc((size + 1) * sizeof(char));// Allocate memory for new
	if (!new)
		return (NULL);
	*(ft_strncpy(new, s + start, size)) = 0;// Copy size characters from s starting at start to new
	return (new);// Return new
}