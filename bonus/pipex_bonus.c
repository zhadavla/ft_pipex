/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 13:14:44 by mnurlybe          #+#    #+#             */
/*   Updated: 2023/08/05 17:57:59 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void do_fork(t_pipex *pipex, int mode, char *argv, char **env)
{
    if (fork() == 0)
    {
        if (mode == FIRST_FORK)
            ft_dup2(pipex->infile_fd, pipex->fd[1]);
        if (mode == MID_FORK)
            ft_dup2(pipex->fd[pipex->fd_ind], pipex->fd[pipex->fd_ind + 3]);
        if (mode == LAST_FORK)
            ft_dup2(pipex->fd[pipex->fd_ind], pipex->outfile_fd);
        close_fd(pipex);
        ft_execute(argv, env);
    }
}

void fork_and_execute(t_pipex *pipex, int argc, char **argv, char **env)
{
    int j;

    j = 2;
    pipex->fd_ind = 0;
    while (j <= argc - 2)
    {
     
        if (j == 2)
            do_fork(pipex, FIRST_FORK, argv[j], env);
        else if (j == argc - 2)
            do_fork(pipex, LAST_FORK, argv[j], env);
        else
        {
            do_fork(pipex, MID_FORK, argv[j], env);
            pipex->fd_ind += 2;
        }
        j++;
    }
}

int main(int argc, char **argv, char **env)
{
    int status;
    t_pipex pipex;
    init(&pipex, argc, argv);
    
    if (argc < 5)
        return (1);
    
    int i = 0;
    while (i < pipex.fd_count)
    {
        pipe(pipex.fd + i);
        i += 2;
    }
    
    fork_and_execute(&pipex, argc, argv, env);
    close_fd(&pipex);
    
    i = 0;
    while (i < pipex.cmd_count)
    {
        wait(&status);
        i++;
    }
    free(pipex.fd);
    return (0);
}
