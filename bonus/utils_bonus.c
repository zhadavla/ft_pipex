#include "../includes/pipex.h"

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

