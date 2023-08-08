/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 17:55:03 by mnurlybe          #+#    #+#             */
/*   Updated: 2023/08/08 15:30:42 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void init_pipex(t_pipex *pipex, int argc, char **argv) {
    if (ft_strncmp(argv[1], "here_doc", 8) == 0) {
        pipex->infile_name = NULL;
        pipex->limiter = argv[2];
        pipex->fd_pipes_count = 4;
        pipex->is_heredoc = true;
        pipex->cmd_count = 2;
    } else {
        pipex->cmd_count = argc - 3;
        pipex->infile_name = argv[1];
        pipex->fd_pipes_count = (pipex->cmd_count - 1) * 2;
        pipex->is_heredoc = false;
    }
    pipex->outfile_name = argv[argc - 1];
    pipex->fd_pipes = (int *) malloc(sizeof(int) * pipex->fd_pipes_count);
}

void close_fd(t_pipex *pipex) {
    int i;

    i = 0;
    while (i < pipex->fd_pipes_count) {
        close(pipex->fd_pipes[i]);
        i++;
    }
}

int ft_dup2(int fd1, int fd2) {
    if (dup2(fd1, 0) == -1)
        return -1;
    if (dup2(fd2, 1) == -1)
        return -1;
    return 1;
}

char **get_binaries(char **env) {
    int i;

    i = 0;
    while (env[++i])
        if (ft_strnstr(env[i], "PATH=", 5))
            return ft_split(env[i] + 5, ':');
    return (NULL);
}

bool ft_execute(char *str, char **env) {
        char **cmd;
        char **path;
        char *pathname;
        int i;

        cmd = ft_split(str, ' ');
        path = get_binaries(env);
        i = 0;
        while (path[i] != NULL) {
            pathname = ft_join(path[i], "/");
            pathname = ft_strjoin(pathname, cmd[0]);
            if (access(pathname, X_OK) == 0) {
                //free(pathname);
                //free_split(cmd);
                free_split(path);
                execve(pathname, cmd, env);
            }
            free(pathname);
            i++;
        }
//    free(pathname);
        free_split(cmd);
        free_split(path);
        return false;
    }

