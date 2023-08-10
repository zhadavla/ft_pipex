/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:06:43 by vzhadan           #+#    #+#             */
/*   Updated: 2023/08/10 17:19:41 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "ft_printf.h"
# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define PIPE_IN 0
# define PIPE_OUT 1

# define FIRST_FORK 1
# define MID_FORK 2
# define LAST_FORK 3

# define TRUE 1
# define FALSE 0
//# define int int

typedef struct s_pipex
{
	int		fd_pipes_count;
	int		cmd_count;
	int		infile_fd;
	int		outfile_fd;
	int		*fd_pipes;
	int		fd_ind;
	int	is_heredoc;
	char	*infile_name;
	char	*outfile_name;
	char	*limiter;
}			t_pipex;

/*
 * returns an array of possible paths to the comands
 * from the PATH variable in the environment
 */
char		**get_binaries(char **env);
int		ft_execute(char *argv, char **env);
char		*ft_join(char const *s1, char const *s2);
int			ft_dup2(int fd1, int fd2);
void		close_fd(t_pipex *pipex);
void		free_split(char **strs);
void		heredoc(t_pipex *pipex);
void		init_pipex(t_pipex *pipex, int argc, char **argv);
int			open_file(char *filename, int is_heredoc, int is_input);
void		free_split(char **strs);
void		ft_close(t_pipex *pipex);
char		*ft_join(char const *s1, char const *s2);
char		**create_cmd_list(char **argv, int argc, t_pipex *pipex);
int			check_argv(char **argv, int argc, t_pipex *pipex, char **env);
int		command_check(char *str, char **env);
#endif
