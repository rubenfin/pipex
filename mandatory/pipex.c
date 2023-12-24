/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/18 15:29:18 by rfinneru      #+#    #+#                 */
/*   Updated: 2023/12/16 14:42:03 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_one(int *fd, char *argv[], char *envp[])
{
	int	infile;

	if (access(argv[1], F_OK) == -1 || access(argv[1], R_OK) == -1)
	{
		perror("command not found");
		exit(EXIT_FAILURE);
	}
	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
		exit(EXIT_FAILURE);
	close(fd[0]);
	dup2(infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(infile);
	close(fd[1]);
	find_path(argv[2], envp);
}

void	child_two(int *fd, char *argv[], char *envp[])
{
	int	outfile;

	if (access(argv[4], F_OK) == 0 && access(argv[4], W_OK) == -1)
	{
		perror("outfile");
		exit(EXIT_FAILURE);
	}
	outfile = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0664);
	if (outfile == -1)
		exit(EXIT_FAILURE);
	close(fd[1]);
	dup2(outfile, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(outfile);
	find_path(argv[3], envp);
}

int	pipex(char *argv[], char *envp[])
{
	pid_t	child1;
	pid_t	child2;
	int		fd[2];
	int		status;

	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	child1 = fork();
	if (child1 == -1)
		exit(EXIT_FAILURE);
	if (child1 == 0)
		child_one(fd, argv, envp);
	child2 = fork();
	if (child2 == -1)
		exit(EXIT_FAILURE);
	if (child2 == 0)
		child_two(fd, argv, envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);
	return (check_status(status));
}

int	main(int argc, char *argv[], char *envp[])
{
	if (argc == 5)
		return (pipex(argv, envp));
	else
	{
		perror("usage: ./pipex infile \"cmd1\" \"cmd2\" outfile");
		exit(EXIT_FAILURE);
	}
	return (0);
}
