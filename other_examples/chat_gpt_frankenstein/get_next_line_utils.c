/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smishos <smishos@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 10:37:01 by smishos           #+#    #+#             */
/*   Updated: 2024/05/09 12:16:03 by smishos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// The functions ft_strdup, ft_strchr, ft_strjoin, and ft_strcut
// are helper functions
// that you should implement in your get_next_line_utils.c file.
#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	length;

	length = 0;
	while (s[length] != 0)
		length++;
	return (length);
}

void	*ft_memset(void *b, int c, size_t length)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)b;
	while (length > 0)
	{
		*(ptr) = (unsigned char)c;
		ptr++;
		length--;
	}
	return (b);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
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

void	*ft_calloc(size_t count, size_t size)
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
		return (NULL);
	if (ptr)
		ft_memset(ptr, 0, total_size);
	return (ptr);
}
