# ft_pipex with the bonus part

Project aimed at studying how to work with multiple processes in C using the **pipe** and **fork** functions.

Just run ```make``` to compile it.

Program will be executed as follows:
```./pipex file1 cmd1 cmd2 cmd3 ... file2``` by cmd1 cmd2 cmd3 meaning any number of shell commands.
It must take at least 4 arguments:
  - file1 and file2 are file names.
  - cmd1 and cmd2 are shell commands with their parameters.

It must behave exactly the same as the shell command below:
```$> < file1 cmd1 | cmd2 > file2```

## Bonus part
You will get extra points if you:
  1. Handle multiple pipes.
This:
```./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2```
Should behave like:
```< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2```
  2. Support « and » when the first parameter is "here_doc".
This:
```./pipex here_doc LIMITER cmd cmd1 file```
Should behave like:
```cmd << LIMITER | cmd1 >> file```




