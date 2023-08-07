/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:06:43 by vzhadan           #+#    #+#             */
/*   Updated: 2023/08/07 14:43:53 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include "ft_printf.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define PIPE_IN 0
# define PIPE_OUT 1

# define FIRST_FORK 1
# define MID_FORK 2
# define LAST_FORK 3

# define true 1 
# define false 0
# define bool int

typedef struct s_pipex
{
    int fd_pipes_count;
    int cmd_count;
    int infile_fd;
    int outfile_fd;
    int *fd_pipes;
    int fd_ind;
    bool is_heredoc; 
    char *infile_name;
    char *outfile_name;
    char *limiter;
}   t_pipex;

/*
 * returns an array of possible paths to the comands 
 * from the PATH variable in the environment
*/
char **get_binaries(char **env);
void ft_execute(char *argv, char **env);
void    ft_dup2(int fd1, int fd2);
void    close_fd(t_pipex *pipex);
void init(t_pipex *pipex, int argc, char **argv);


#endif
