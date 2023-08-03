#include "../includes/pipex.h"

void pipes(char *cmd, char **env)
{
    int pipe_end[2];
    int pid[2]; 

    if (pipe(pipe_end) == -1)
        return ; 

    pid[0] = fork();
    if (pid[0] == 0)
    {
        close(pipe_end[PIPE_IN]);
        dup2(pipe_end[1], STDOUT_FILENO);
        // close(pipe_end[PIPE_OUT]);
        ft_execute(cmd, env);
    }

    pid[1] = fork();
    if (pid[1] == 0)
    {
        close(pipe_end[PIPE_OUT]);
        dup2(pipe_end[0], STDIN_FILENO);
        // close(pipe_end[PIPE_IN]);
        ft_execute(cmd, env);
    }
    waitpid(pid[0], NULL, 0);
    waitpid(pid[1], NULL, 0);
}


int main (int argc, char **argv, char **env)
{
    int i;
    int fd_infile;
    int fd_outfile;

    if (argc < 5)
        return (0);

    fd_infile = open(argv[1], O_RDONLY);
    dup2(fd_infile, STDIN_FILENO);

    fd_outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
    dup2(fd_outfile, STDOUT_FILENO);

    i = 2;
    while (i <= argc - 2)
    {
        // printf("%s\n", argv[i]);
        // int pipe_end[2];
        // int pid[2]; 

        // if (pipe(pipe_end) == -1)
        //     return 1; 

        // pid[0] = fork();
        // if (pid[0] == 0)
        // {
        //     dup2(pipe_end[1], STDOUT_FILENO);
        //     close(pipe_end[PIPE_OUT]);
        //     close(pipe_end[PIPE_IN]);
        //     ft_execute(argv[i], env);
        // }

        // pid[1] = fork();
        // if (pid[1] == 0)
        // {
        //     dup2(pipe_end[0], STDIN_FILENO);
        //     close(pipe_end[PIPE_IN]);
        //     close(pipe_end[PIPE_OUT]);
        //     ft_execute(argv[i], env);
        // }
        // waitpid(pid[0], NULL, 0);
        // waitpid(pid[1], NULL, 0);
        pipes(argv[i], env);
        i++;
    }

    close(fd_infile);
    close(fd_outfile);

    return (0);
}