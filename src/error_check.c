/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 20:40:15 by mnurlybe          #+#    #+#             */
/*   Updated: 2023/08/15 16:57:52 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	command_check(char *str, char **env)
{
	char	**cmd;
	char	**path;
	char	*pathname;
	int		i;

	cmd = ft_split(str, ' ');
	path = get_binaries(env);
	i = 0;
	while (path[i] != NULL)
	{
		pathname = ft_join(path[i], "/");
		pathname = ft_strjoin(pathname, cmd[0]);
		if (access(pathname, X_OK) == 0)
		{
			free(pathname);
			free_split(cmd);
			free_split(path);
			return (TRUE);
		}
		free(pathname);
		i++;
	}
	free_split(cmd);
	free_split(path);
	return (FALSE);
}

int	check_argv(char **argv, int argc, t_pipex *pipex, char **env)
{
	int	i;

	i = 2;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		if (argc != 6)
			return (-1);
		pipex->is_heredoc = TRUE;
	}
	else
	{
		if (argc < 5)
			return (-1);
		pipex->is_heredoc = FALSE;
	}
	if (pipex->is_heredoc)
		i = 3;
	while (i < argc - 1)
	{
		if (!command_check(argv[i], env))
			return (-1);
		i++;
	}
	return (1);
}
