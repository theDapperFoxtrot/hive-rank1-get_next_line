/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smishos <smishos@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 13:14:30 by smishos           #+#    #+#             */
/*   Updated: 2024/05/11 15:08:21 by smishos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

char	*get_next_line(int fd);

int main()
{
	int fd;
    char *line;

    // Open a file for reading
    fd = open("bible.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Call get_next_line in a loop to read lines from the file
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s\n", line);
    }

    // Close the file descriptor
    close(fd);
	return (0);
}
