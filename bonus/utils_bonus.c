/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 17:55:03 by mnurlybe          #+#    #+#             */
/*   Updated: 2023/08/07 15:14:54 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void init(t_pipex *pipex, int argc, char **argv)
{
    pipex->cmd_count = argc - 3;
    pipex->fd_pipes_count = (pipex->cmd_count - 1) * 2;
    pipex->infile_fd = open(argv[1], O_RDONLY);
    pipex->outfile_fd = open(argv[argc-1], O_WRONLY | O_CREAT | O_TRUNC, 0777); 
    pipex->fd_pipes = (int*)malloc(sizeof(int) * pipex->fd_pipes_count);
    pipex->is_heredoc = false;
}

void    close_fd(t_pipex *pipex)
{
    int i;

    i = 0;
    while (i < pipex->fd_pipes_count)
    {
        close(pipex->fd_pipes[i]);
        i++;
    }
}

void    ft_dup2(int fd1, int fd2)
{
    dup2(fd1, 0);
    dup2(fd2, 1);
}

char **get_binaries(char **env){
	char **paths;
	int i;
	
	i = 0;
	while (env[++i])
		if (ft_strnstr(env[i], "PATH=", 5))
			return ft_split(env[i] + 5, ':');
	return (paths);
}

void ft_execute(char *argv, char **env)
{
    char **cmd;
    char **path;

    char *pathname;
    int i;
    
    cmd = ft_split(argv, ' ');
    path = get_binaries(env);
    i = 0;
    while (path[i] != NULL)
    {
        pathname = ft_strjoin(path[i], "/");
        pathname = ft_strjoin(pathname, cmd[0]);
        if (access(pathname, X_OK) == 0)
            execve(pathname, cmd, env);
        free(pathname);
        i++;
    }
    free(cmd);
}

