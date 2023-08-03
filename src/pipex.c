/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:56:41 by vzhadan           #+#    #+#             */
/*   Updated: 2023/08/03 20:51:24 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void child_process_one(char **argv, int *pipe_end, char **env)
{
    int fd_infile;
    
    fd_infile = open(argv[1], O_RDONLY);
    dup2(fd_infile, STDIN_FILENO);
    dup2(pipe_end[1], STDOUT_FILENO);
    close(pipe_end[1]);
    close(pipe_end[0]);
    close(fd_infile);
    
    ft_execute(argv[2], env);
    
    //add error handler, free and exit for fd, dup2, execve; 
}
    
void child_process_two(char **argv, int *pipe_end, char **env)
{
    int fd_outfile;
    
    fd_outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
    
    dup2(fd_outfile, STDOUT_FILENO);
    dup2(pipe_end[0], STDIN_FILENO);
    close(pipe_end[PIPE_IN]);
    close(pipe_end[PIPE_OUT]);
    close(fd_outfile);

    ft_execute(argv[3], env);
}

int main(int argc, char **argv, char **env)
{    
    if (argc != 5)
        return (0);
    int pipe_end[2];
    int  pid[2];

    if (pipe(pipe_end) == -1)
        return 1;  //add error handler and exit
    
    pid[0] = fork();
    if (pid[0] == 0)
        child_process_one(argv, pipe_end, env);
        
    pid[1] = fork();
    if (pid[1] == 0)
        child_process_two(argv, pipe_end, env);
    
    close(pipe_end[PIPE_IN]);
    close(pipe_end[PIPE_OUT]);
    
    waitpid(pid[0], NULL, 0);
    waitpid(pid[1], NULL, 0);
    return (0);
}
