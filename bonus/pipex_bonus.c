/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 13:14:44 by mnurlybe          #+#    #+#             */
/*   Updated: 2023/08/05 21:19:41 by mnurlybe         ###   ########.fr       */
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
     
        if (j == 2 || (j == 3 && pipex->is_heredoc))
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

int heredoc(t_pipex *pipex, char *limiter, char **env)
{
    char *line;
    int fd;
    int len;

    fd = open("tmpfile", O_WRONLY | O_CREAT, 0777);
    while (1)
    {
        ft_printf("heredoc> ");
        line = get_next_line(0);
        write(fd, line, ft_strlen(line));
        if (!ft_strncmp(line, limiter, ft_strlen(limiter)))
            // exit(EXIT_SUCCESS);
            break;
    }
    return (fd);
}

void do_fork_names(t_pipex *pipex, int mode, char *cmd, char **env)
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
        ft_execute(cmd, env);
    }
}

int open_file(char *filename, bool is_here_doc, bool is_input)
{

    
    if (is_here_doc)   
        return open(filename, O_WRONLY | O_CREAT | O_APPEND, 0777); 
    else if (is_input)
        return open(filename, O_RDONLY, 0777); 
    else
        return open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
        
}

void execute_command(t_pipex *pipex, int num_of_commands, char **list_of_commands)
{
    int fd_in;
    int fd_out;
    int j;
    
    fd_in = open(...
    fd_out = open
    j = 0;
    while (j < num_of_commands)
    {
        if (j == 0)
            do_fork_names(pipex, FIRST_FORK, list_of_commands[j], env);
        else if (j == num_of_commands - 1)
            do_fork_names(pipex, LAST_FORK, list_of_commands[j], env);
        else
        {
            do_fork_names(pipex, MID_FORK, list_of_commands[j], env);
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
    
    if (ft_strncmp(argv[1], "here_doc", 8) == 0)
    {
        pipex.infile_fd = heredoc(&pipex, argv[2], env);
        pipex.fd_count = 2;
        pipex.is_heredoc = true;
    }
        
    int i = 0;
    while (i < pipex.fd_count)
    {
        pipe(pipex.fd + i);
        i += 2;
    }
    
    execute_command(&pipex, argc, list_of_commands);
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
