/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 13:14:44 by mnurlybe          #+#    #+#             */
/*   Updated: 2023/08/05 15:18:05 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void init(t_pipex *pipex, int argc, char **argv)
{
    pipex->fd_count = (argc - 1) * 2;
    pipex->cmd_count = argc - 3;
    pipex->infile_fd = open(argv[1], O_RDONLY);
    pipex->outfile_fd = open(argv[argc-1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
    pipex->fd = (int*)malloc(sizeof(int) * pipex->fd_count);
}

void    first_fork(t_pipex *pipex, char *argv, char **env)
{
    int i;
    
    if (fork() == 0)
    {
        dup2(pipex->infile_fd, 0);
        dup2(pipex->fd[1], 1);
        
        i = 0;
        while (i < pipex->fd_count)
        {
            close(pipex->fd[i]);
            i++;
        }
        ft_execute(argv, env);
    }
    
}

void    middle_fork(t_pipex *pipex, char *argv, char **env)
{
    int i;
    
    if (fork() == 0)
    {
        dup2(pipex->fd[pipex->j], 0);
        dup2(pipex->fd[pipex->j + 3], 1);

        i = 0;
        while (i < pipex->fd_count)
        {
            close(pipex->fd[i]);
            i++;
        }
        ft_execute(argv, env);
    }
}

void    last_fork(t_pipex *pipex, char *argv, char **env)
{
    int i;
    
    if (fork() == 0)
    {
        dup2(pipex->fd[pipex->j], 0);
        dup2(pipex->outfile_fd, 1);
        
        i = 0;
        while (i < pipex->fd_count)
        {
            close(pipex->fd[i]);
            i++;
        }
        ft_execute(argv, env);
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
    
    // forking starts here

    first_fork(&pipex, argv[2], env);
    int j = 3;
    pipex.j = 0;
    while (j < argc - 2)
    {
        middle_fork(&pipex, argv[j], env);
        pipex.j += 2;
        j++; 
    }
    last_fork(&pipex, argv[j], env);

    i = 0;
    while (i < pipex.fd_count)
    {
        close(pipex.fd[i]);
        i++;
    }
    i = 0;
    while (i < pipex.cmd_count)
    {
        wait(&status);
        // waitpid(pid[i], NULL, 0);
        i++;
    }
    free(pipex.fd);
    return (0);
}
