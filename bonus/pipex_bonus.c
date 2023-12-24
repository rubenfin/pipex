/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_bonus.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/09 14:30:30 by rfinneru      #+#    #+#                 */
/*   Updated: 2023/12/20 12:21:03 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	do_first_cmd(t_pipes pipes, char *argv[], char **envp)
{
	int	infile;

	if (access(argv[1], F_OK) == -1 || access(argv[1], R_OK) == -1)
	{
		perror("infile not found");
		exit(EXIT_FAILURE);
	}
	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
		exit(EXIT_FAILURE);
	close(pipes.curr_read);
	dup2(infile, STDIN_FILENO);
	dup2(pipes.curr_write, STDOUT_FILENO);
	find_path(argv[2], envp);
}

void	do_middle_cmd(t_pipes pipes, char *argv, char **envp)
{
	dup2(pipes.prev_read, STDIN_FILENO);
	dup2(pipes.curr_write, STDOUT_FILENO);
	find_path(argv, envp);
}

void	do_last_cmd(int argc, t_pipes pipes, char *argv[], char **envp)
{
	int	outfile;

	if (access(argv[argc - 1], F_OK) == 0 && access(argv[argc - 1], W_OK) == -1)
	{
		perror("outfile");
		exit(EXIT_FAILURE);
	}
	outfile = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0664);
	if (outfile == -1)
	{
		perror("reading outfile");
		exit(EXIT_FAILURE);
	}
	dup2(pipes.curr_read, STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	find_path(argv[argc - 2], envp);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipes	pipes;
	int		i;
	int		status;
	int		pid;

	pid = 0;
	argc_heredoc_check(argc, argv, envp);
	status = 0;
	ft_bzero(&pipes, sizeof(t_pipes));
	setup_first_cmd(&pipes, argv, envp);
	i = 0;
	while (i < argc - 5)
		setup_middle_cmd(&pipes, argv[3 + i++], envp);
	close(pipes.curr_write);
	setup_last_cmd(argc, pipes, argv, envp);
	wait_for_processes(pid, argc, &status);
	close_pipes(pipes);
	return (check_status(status));
}
