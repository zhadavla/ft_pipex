/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 13:14:44 by mnurlybe          #+#    #+#             */
/*   Updated: 2023/08/08 15:30:39 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void heredoc(t_pipex *pipex) {
    char *line;

    while (1) {
        ft_printf("heredoc> ");
        line = get_next_line(0);
        write(pipex->fd_pipes[1], line, ft_strlen(line));
        if (!ft_strncmp(line, pipex->limiter, ft_strlen(pipex->limiter))) {
            free(line);
            break;
        }
        free(line);
    }
}

int do_fork_names(t_pipex *pipex, int mode, char *cmd, char **env) {
    int x = fork();
    int dup_check = 1;
    if (x == 0) {
        if (mode == FIRST_FORK) {
            if (pipex->is_heredoc)
                dup_check = ft_dup2(pipex->fd_pipes[0], pipex->fd_pipes[3]);
            else
                dup_check = ft_dup2(pipex->infile_fd, pipex->fd_pipes[1]);
        }
        if (mode == MID_FORK)
            dup_check = ft_dup2(pipex->fd_pipes[pipex->fd_ind], pipex->fd_pipes[pipex->fd_ind + 3]);
        if (mode == LAST_FORK) {
            if (pipex->is_heredoc)
                dup_check = ft_dup2(pipex->fd_pipes[2], pipex->outfile_fd);
            else
                dup_check = ft_dup2(pipex->fd_pipes[pipex->fd_ind], pipex->outfile_fd);
        }
        close_fd(pipex);
        if (dup_check == -1)
            return dup_check;
        ft_execute(cmd, env);
    } else if (x == -1) {
        perror("");
        return -1;
    }
    return 1;
}

int open_file(char *filename, bool is_heredoc, bool is_input) {
    if (is_heredoc && !is_input)
        return open(filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
    if (is_input)
        return open(filename, O_RDONLY, 0777);
    else
        return open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
}

int execute_command(t_pipex *pipex, int num_of_commands, char **list_of_commands, char **env) {
    int j;

    if (pipex->infile_name)
        pipex->infile_fd = open_file(pipex->infile_name, pipex->is_heredoc, 1);
    pipex->outfile_fd = open_file(pipex->outfile_name, pipex->is_heredoc, 0);

    if ((pipex->infile_name && pipex->infile_fd == -1) || pipex->outfile_fd == -1) {
        perror("Error when opening file");
        return -1;
    }
    if (pipex->is_heredoc)
        heredoc(pipex);
    j = 0;
    int is_error;
    pipex->fd_ind = 0;
    while (j < num_of_commands) {
        if (j == 0)
            is_error = do_fork_names(pipex, FIRST_FORK, list_of_commands[j], env);
        else if (j == num_of_commands - 1)
            is_error = do_fork_names(pipex, LAST_FORK, list_of_commands[j], env);
        else {
            is_error = do_fork_names(pipex, MID_FORK, list_of_commands[j], env);
            pipex->fd_ind += 2;
        }
        j++;
        if (is_error == -1)
            return -1;
    }
    return 1;
}

char **create_list_of_commands(char **argv, int argc, t_pipex *pipex) {
    char **commands;

    if (pipex->is_heredoc) {
        commands = argv + 3;
        commands[2] = NULL;
        return commands;
    }
    commands = argv + 2;
    commands[argc - 1 - 2] = NULL;
    return commands;
}



void free_split(char **strs)
{
    int i = 0;
    while (strs[i]){
        free(strs[i]);
        i++;
    }
    free(strs);
}

char	*ft_join(char const *s1, char const *s2)
{
    size_t	len1;
    size_t	len2;
    char	*str;

    len1 = ft_strlen(s1);
    len2 = ft_strlen(s2);
    str = (char *)malloc(sizeof(char) * (len1 + len2) + 1);
    if (!s1 || !s2)
        return (NULL);
    if (!str)
        return (NULL);
    ft_strlcpy(str, s1, len1 + 1);
    ft_strlcat(str, s2, len2 + len1 + 1);
    return (str);
}

bool command_check(char *str, char **env) {
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
            free(pathname);
            free_split(cmd);
            free_split(path);
            return true;
        }
        free(pathname);

        i++;
    }
//    free(pathname);
    free_split(cmd);
    free_split(path);
    return false;
}

int check_argv(char **argv, int argc, t_pipex *pipex, char **env) {
    int i = 2;
    if (pipex->is_heredoc)
        i = 3;
    while (i < argc - 1) {
        printf("%s\n", argv[i]);
        if (!command_check(argv[i], env))
            return -1;
        i++;
    }
    return 1;
}

int main(int argc, char **argv, char **env) {
    int status;
    char **list_of_commands;
    t_pipex pipex;

    if (argc < 5) {
        return (1);
    }

    if (ft_strncmp(argv[1], "here_doc", 8) == 0)
        pipex.is_heredoc = true;
    else
        pipex.is_heredoc = false;
    if (check_argv(argv, argc, &pipex, env) == -1) {
        perror("");
        return (EXIT_FAILURE);
    }
//
    init_pipex(&pipex, argc, argv);
    int i = 0;
    while (i < pipex.fd_pipes_count) {
        if (pipe(pipex.fd_pipes + i) == -1)
            return (EXIT_FAILURE);
        i += 2;
    }
    list_of_commands = create_list_of_commands(argv, argc, &pipex);
    if (execute_command(&pipex, pipex.cmd_count, list_of_commands, env) == -1) {
        perror("");
        return (EXIT_FAILURE);
    }
    close_fd(&pipex);
    if (pipex.infile_name)
        close(pipex.infile_fd);
    close(pipex.outfile_fd);
    i = 0;
    while (i < pipex.cmd_count) {
        wait(&status);
        i++;
    }
    free(pipex.fd_pipes);
    return (0);
}
