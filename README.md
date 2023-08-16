# ft_pipex 

Project aimed at studying how to work with multiple processes in C using the **pipe** and **fork** functions.

Just run ```make``` to compile it.

Program will be executed as follows:
```./pipex file1 cmd1 cmd2 cmd3 ... file2``` by cmd1 cmd2 cmd3 meaning any number of shell commands.
It must take at least 4 arguments:
  - file1 and file2 are file names.
  - cmd1 and cmd2 are shell commands with their parameters.

It must behave exactly the same as the shell command below:
```$> < file1 cmd1 | cmd2 > file2```
