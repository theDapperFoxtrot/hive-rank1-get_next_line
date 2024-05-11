/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smishos <smishos@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 13:21:41 by smishos           #+#    #+#             */
/*   Updated: 2024/05/11 14:52:09 by smishos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"



size_t	ft_strlen(const char *s)
{
	int	length;

	length = 0;
	while (s[length])
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

char	*ft_strdup(const char *s)
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

