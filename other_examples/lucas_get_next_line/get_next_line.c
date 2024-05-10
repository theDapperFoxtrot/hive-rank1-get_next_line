#include "get_next_line.h"

char	*read_to_cache(char *curr_cache, char *buffer, int fd);
char	*ret_line_clear_cache(char **curr_cache);
char	*free_null(char **str);
char	*ft_substr(char const *s, unsigned int start, size_t size);

char	*get_next_line(int fd)
{
	char			*buffer;
	static char		*cache[OPEN_MAX];

	if (fd < 0 || OPEN_MAX < fd || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer || read(fd, 0, 0) < 0)
	{
		free_null(&cache[fd]);
		return (free_null(&buffer));
	}
	buffer[0] = 0;
	cache[fd] = read_to_cache(cache[fd], buffer, fd);
	if (!cache[fd])
		return (NULL);
	return (ret_line_clear_cache(&cache[fd]));
}

char	*read_to_cache(char *curr_cache, char *buffer, int fd)
{
	ssize_t	bytes;

	bytes = 1;
	while ((!curr_cache || (curr_cache && !ft_strchr(curr_cache, '\n')))
		&& bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes <= 0)
		{
			if (bytes == -1)
				free_null(&curr_cache);
			break ;
		}
		buffer[bytes] = 0;
		curr_cache = gnl_join(curr_cache, buffer);
	}
	free(buffer);
	return (curr_cache);
}

char	*ret_line_clear_cache(char **curr_cache)
{
	char			*tmp;
	char			*line;
	char			*pt_to_n;
	size_t			len;

	pt_to_n = ft_strchr(*curr_cache, '\n');
	len = pt_to_n - *curr_cache + 1;
	line = ft_substr(*curr_cache, 0, len);
	if (!line)
		return (free_null(curr_cache));
	if (!pt_to_n || !curr_cache[0][len])
	{
		free_null(curr_cache);
		return (line);
	}
	tmp = *curr_cache;
	*curr_cache = ft_substr(*curr_cache, len, ft_strlen(*curr_cache) - len);
	if (!*curr_cache)
		*curr_cache = NULL;
	free_null(&tmp);
	return (line);
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

	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	chr_left = ft_strlen(s + start);
	if (size > chr_left)
		size = chr_left;
	new = (char *) malloc((size + 1) * sizeof(char));
	if (!new)
		return (NULL);
	*(ft_strncpy(new, s + start, size)) = 0;
	return (new);
}
