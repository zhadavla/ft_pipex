#include "../includes/pipex.h"

void	heredoc(t_pipex *pipex)
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
			break ;
		}
		free(line);
	}
}