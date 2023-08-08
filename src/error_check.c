#include "../includes/pipex.h"

BOOL	command_check(char *str, char **env)
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
		pipex->is_heredoc = TRUE;
	else
		pipex->is_heredoc = FALSE;
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