/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smishos <smishos@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:23:25 by smishos           #+#    #+#             */
/*   Updated: 2024/05/08 16:20:41 by smishos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h> // For file operations

int main() {
    int fd;
    char *line;

    // Open a file for reading
    fd = open("./test_file.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Call get_next_line in a loop to read lines from the file
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line); // Free memory allocated by get_next_line
    }

    // Close the file descriptor
    close(fd);

    return 0;
}
