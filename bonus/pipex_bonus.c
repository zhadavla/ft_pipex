/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 13:14:44 by mnurlybe          #+#    #+#             */
/*   Updated: 2023/08/05 19:03:11 by vzhadan          ###   ########.fr       */
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

void heredoc(t_pipex *pipex, char *limiter, char **env)
{
    char *line;
    int fd;
    int len;

    fd = open("tmpfile", O_WRONLY | O_CREAT | O_APPEND, 0777);
    while (1)
    {
        ft_printf("heredoc> ");
        line = get_next_line(0);
        write(fd, line, ft_strlen(line));
        if (!ft_strncmp(line, limiter, ft_strlen(limiter)))
            exit(EXIT_SUCCESS);
    }
}

int main(int argc, char **argv, char **env)
{
    int status;
    t_pipex pipex;
    init(&pipex, argc, argv);
    
    if (ft_strncmp(argv[1], "here_doc", 7) == 0){
        heredoc(&pipex, argv[2], env);
        
    }
        
        
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
