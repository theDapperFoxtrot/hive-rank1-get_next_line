#include "get_next_line.h"

char	*read_to_cache(char *curr_cache, char *buffer, int fd);
char	*ret_line_clear_cache(char **curr_cache);
char	*free_null(char **str);
char	*ft_substr(char const *s, unsigned int start, size_t size);

// Get next line from file descriptor
char	*get_next_line(int fd)
{
	char			*buffer;
	static char		*cache[OPEN_MAX];
// Check if file descriptor is valid and if BUFFER_SIZE is valid
	if (fd < 0 || OPEN_MAX < fd || BUFFER_SIZE <= 0)
		return (NULL);
		// Allocate memory for buffer
	buffer = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	// Check if buffer is NULL or if read fails
	if (!buffer || read(fd, 0, 0) < 0)
	{
		free_null(&cache[fd]);
		return (free_null(&buffer));
	}
	// Set buffer to null terminator
	buffer[0] = 0;
	// Read to cache
	cache[fd] = read_to_cache(cache[fd], buffer, fd);
	// Return line from cache
	if (!cache[fd])
		return (NULL);
	return (ret_line_clear_cache(&cache[fd]));
}

char	*read_to_cache(char *curr_cache, char *buffer, int fd)
{
	ssize_t	bytes;

	bytes = 1;
	// Read from file descriptor into buffer
	while ((!curr_cache || (curr_cache && !ft_strchr(curr_cache, '\n')))
		&& bytes > 0)
	{
		// Read from file descriptor into buffer
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes <= 0)
		{
			if (bytes == -1)
				free_null(&curr_cache);
			break ;
		}
		// Set null terminator at end of buffer
		buffer[bytes] = 0;
		// Join buffer to cache
		curr_cache = gnl_join(curr_cache, buffer);
	}
	// Free buffer
	free(buffer);
	return (curr_cache);
}
// Return line from cache
char	*ret_line_clear_cache(char **curr_cache)
{
	char			*tmp;
	char			*line;
	char			*pt_to_n;
	size_t			len;

	pt_to_n = ft_strchr(*curr_cache, '\n'); // Check for newline in cache
	len = pt_to_n - *curr_cache + 1; // Get length of line
	line = ft_substr(*curr_cache, 0, len);// Get line from cache
	if (!line)
		return (free_null(curr_cache)); // Free cache if line is NULL
	if (!pt_to_n || !curr_cache[0][len])// If no newline or newline is at end of cache
	{
		free_null(curr_cache);// Free cache
		return (line);// Return line
	}
	tmp = *curr_cache;// Set temp to cache
	*curr_cache = ft_substr(*curr_cache, len, ft_strlen(*curr_cache) - len);// Set cache to rest of cache
	if (!*curr_cache)// If cache is NULL
		*curr_cache = NULL;// Set cache to NULL
	free_null(&tmp);// Free temp
	return (line);// Return line
}

char	*free_null(char **str)
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
