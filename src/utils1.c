/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 20:29:17 by mnurlybe          #+#    #+#             */
/*   Updated: 2023/08/15 16:57:52 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	open_file(char *filename, int is_heredoc, int is_input)
{
	if (is_heredoc && !is_input)
		return (open(filename, O_WRONLY | O_CREAT | O_APPEND, 0777));
	if (is_input)
		return (open(filename, O_RDONLY, 0777));
	else
		return (open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777));
}

char	**create_cmd_list(char **argv, int argc, t_pipex *pipex)
{
	char	**commands;

	if (pipex->is_heredoc)
	{
		commands = argv + 3;
		commands[2] = NULL;
		return (commands);
	}
	commands = argv + 2;
	commands[argc - 1 - 2] = NULL;
	return (commands);
}

void	free_split(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
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

void	ft_close(t_pipex *pipex)
{
	close_fd(pipex);
	if (pipex->infile_name)
		close(pipex->infile_fd);
	close(pipex->outfile_fd);
}
