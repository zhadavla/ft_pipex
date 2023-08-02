/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:56:41 by vzhadan           #+#    #+#             */
/*   Updated: 2023/08/02 18:56:43 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void)
{
    int fd = open("infile", O_RDONLY);

    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

 
    // Duplicate the file descriptor to STDIN_FILENO (fd will be copied to STDIN)
    if (dup2(fd, STDIN_FILENO) == -1) {
        perror("Error duplicating file descriptor");
        return 1;
    }

    // Close the original file descriptor as it's no longer needed
    close(fd);

    // Execute the 'wc' command to count the lines from the file
    char *arr[] = {"wc", "-l", NULL};
    execv("/bin/wc", arr);

    // execv will not return if successful, so this code will only be reached in case of an error
    perror("Error executing wc");
    return 1;
}
