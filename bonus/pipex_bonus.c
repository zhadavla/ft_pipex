/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 13:14:44 by mnurlybe          #+#    #+#             */
/*   Updated: 2023/08/07 18:31:33 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void heredoc(t_pipex *pipex)
{
    char *line;

    while (1)
    {
        ft_printf("heredoc> ");
        line = get_next_line(0);
        write(pipex->fd_pipes[1], line, ft_strlen(line));
        if (!ft_strncmp(line, pipex->limiter, ft_strlen(pipex->limiter)))
        {
            free(line);
            break;
        }
        free(line);
    }
    // close(pipex->fd_pipes[1]); ???
}

void do_fork_names(t_pipex *pipex, int mode, char *cmd, char **env)
{
    if (fork() == 0)
    {
        if (mode == FIRST_FORK)
        {
            if (pipex->is_heredoc)
                ft_dup2(pipex->fd_pipes[0], pipex->fd_pipes[3]);
            else
                ft_dup2(pipex->infile_fd, pipex->fd_pipes[1]);
        }
        if (mode == MID_FORK)
            ft_dup2(pipex->fd_pipes[pipex->fd_ind], pipex->fd_pipes[pipex->fd_ind + 3]);
        if (mode == LAST_FORK)
        {
            if (pipex->is_heredoc)
                ft_dup2(pipex->fd_pipes[2], pipex->outfile_fd);
            else
                ft_dup2(pipex->fd_pipes[pipex->fd_i nd], pipex->outfile_fd);
        }
        close_fd(pipex);
        ft_execute(cmd, env);
    }
}

int open_file(char *filename, bool is_heredoc, bool is_input)
{
    if (is_heredoc)
        return open(filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
    if (is_input)
        return open(filename, O_RDONLY, 0777);
    else
        return open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);           
}

void execute_command(t_pipex *pipex, int num_of_commands, char **list_of_commands, char **env)
{
    int j;

    pipex->infile_fd = open_file(pipex->infile_name, pipex->is_heredoc, 1);
    pipex->outfile_fd = open_file(pipex->outfile_name, pipex->is_heredoc, 0);

    if (pipex->is_heredoc)
        heredoc(pipex);
        
    j = 0;
    pipex->fd_ind = 0;
    while (j < num_of_commands)
    {
        if (j == 0)
            do_fork_names(pipex, FIRST_FORK, list_of_commands[j], env);
        else if (j == num_of_commands - 1)
            do_fork_names(pipex, LAST_FORK, list_of_commands[j], env);
        else
            do_fork_names(pipex, MID_FORK, list_of_commands[j], env);
            pipex->fd_ind += 2;
        j++;
    }
    
}

char **create_list_of_commands(char **argv, int argc, t_pipex *pipex)
{
    char **commands;

    if (pipex->is_heredoc)   
    {
        commands = argv + 3;
        commands[2] = NULL;
        return commands;
    } 
    commands = argv + 2;
    commands[argc - 1 - 2] = NULL;
    return commands;
}

int main(int argc, char **argv, char **env)
{
    int status;
    char **list_of_commands;
    t_pipex pipex;
    
    if (argc < 5)
        return (1);
        
    init(&pipex, argc, argv);
    
    int i = 0;
    while (i < pipex.fd_pipes_count)
    {
        pipe(pipex.fd_pipes + i);
        i += 2;
    }

    list_of_commands = create_list_of_commands(argv, argc, &pipex);
    execute_command(&pipex, pipex.cmd_count, list_of_commands, env);

    close_fd(&pipex);
    close(pipex.infile_fd);
    close(pipex.outfile_fd);
    
    i = 0;
    while (i < pipex.cmd_count)
    {
        wait(&status);
        i++;
    }
    free(pipex.fd_pipes);
    return (0);
}
