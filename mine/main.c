/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smishos <smishos@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 13:14:30 by smishos           #+#    #+#             */
/*   Updated: 2024/05/15 15:14:52 by smishos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

char	*get_next_line(int fd);

int	main(void)
{
	int		fd[8];
	int		i;
	char	*line;
	int	eof[8] = {0}; // Array to track EOF status for each file descriptor

	// Open a file for reading
	fd[0] = open("bible.txt", O_RDONLY);
	fd[1] = open("test1.txt", O_RDONLY);
	fd[2] = open("test2.txt", O_RDONLY);
	fd[3] = open("test3.txt", O_RDONLY);
	fd[4] = open("test4.txt", O_RDONLY);
	fd[5] = open("test5.txt", O_RDONLY);
	fd[6] = open("timeout1.txt", O_RDONLY);
	fd[7] = open("timeout2.txt", O_RDONLY);

	i = 0;
	while (1)
	{
		if (!eof[i]) // Check if EOF has not been reached for this file descriptor
		{
			line = get_next_line(fd[i]);
			if (!line)
			{
				eof[i] = 1; // Mark EOF for this file descriptor
			}
			else
			{
				printf("%s", line);
				free(line);
			}
		}

		i++;
		if (i == 8)
			i = 0;

		// Check if all file descriptors have reached EOF
		int	all_eof = 1;
		for (int j = 0; j < 8; j++)
		{
			if (!eof[j])
			{
				all_eof = 0;
				break;
			}
		}
		if (all_eof)
			break; // Exit the loop if all file descriptors have reached EOF
	}

	// Close all file descriptors
	for (int j = 0; j < 8; j++)
	{
		close(fd[j]);
	}

	return (0);
}
