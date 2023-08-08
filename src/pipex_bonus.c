/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 13:14:44 by mnurlybe          #+#    #+#             */
/*   Updated: 2023/08/08 20:41:42 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	do_fork_names(t_pipex *pipex, int mode, char *cmd, char **env)
{
	int	x;
	int	dup_check;

	x = fork();
	dup_check = 1;
	if (x == 0)
	{
		if (pipex->is_heredoc && mode == FIRST_FORK)
			dup_check = ft_dup2(pipex->fd_pipes[0], pipex->fd_pipes[3]);
		else if (mode == FIRST_FORK)
			dup_check = ft_dup2(pipex->infile_fd, pipex->fd_pipes[1]);
		if (mode == MID_FORK)
			dup_check = ft_dup2(pipex->fd_pipes[pipex->fd_ind], \
				pipex->fd_pipes[pipex->fd_ind + 3]);
		if (pipex->is_heredoc && mode == LAST_FORK)
			dup_check = ft_dup2(pipex->fd_pipes[2], pipex->outfile_fd);
		else if (mode == LAST_FORK)
			dup_check = ft_dup2(pipex->fd_pipes[pipex->fd_ind], \
				pipex->outfile_fd);
		close_fd(pipex);
		if (dup_check == -1)
			return (dup_check);
		ft_execute(cmd, env);
	}
	return (x);
}

int	open_error_check(t_pipex *pipex)
{
	if (pipex->infile_name)
		pipex->infile_fd = open_file(pipex->infile_name, pipex->is_heredoc, 1);
	pipex->outfile_fd = open_file(pipex->outfile_name, pipex->is_heredoc, 0);
	if ((pipex->infile_name && pipex->infile_fd == -1)
		|| pipex->outfile_fd == -1)
	{
		perror("Error when opening file");
		return (-1);
	}
	return (1);
}

int	execute_command(t_pipex *pipex, int num_of_commands, char **cmd_list,
		char **env)
{
	int	j;
	int	is_error;

	if (open_error_check(pipex) == -1)
		return (-1);
	if (pipex->is_heredoc)
		heredoc(pipex);
	j = 0;
	pipex->fd_ind = 0;
	while (j < num_of_commands)
	{
		if (j == 0)
			is_error = do_fork_names(pipex, FIRST_FORK, cmd_list[j], env);
		else if (j == num_of_commands - 1)
			is_error = do_fork_names(pipex, LAST_FORK, cmd_list[j], env);
		else
		{
			is_error = do_fork_names(pipex, MID_FORK, cmd_list[j], env);
			pipex->fd_ind += 2;
		}
		j++;
		if (is_error == -1)
			return (-1);
	}
	return (1);
}

int	create_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->fd_pipes_count)
	{
		if (pipe(pipex->fd_pipes + i) == -1)
		{
			free(pipex->fd_pipes);
			return (-1);
		}
		i += 2;
	}
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	int		status;
	char	**cmd_list;
	t_pipex	pipex;
	int		i;

	init_pipex(&pipex, argc, argv);
	if (check_argv(argv, argc, &pipex, env) == -1 || create_pipes(&pipex) == -1)
		return (EXIT_FAILURE);
	cmd_list = create_cmd_list(argv, argc, &pipex);
	if (execute_command(&pipex, pipex.cmd_count, cmd_list, env) == -1)
	{
		free(pipex.fd_pipes);
		perror("");
		return (EXIT_FAILURE);
	}
	ft_close(&pipex);
	i = 0;
	while (i++ < pipex.cmd_count)
		wait(&status);
	free(pipex.fd_pipes);
	return (0);
}
