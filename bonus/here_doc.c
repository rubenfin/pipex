/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_doc.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 16:28:38 by rfinneru      #+#    #+#                 */
/*   Updated: 2023/12/15 18:13:50 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "gnl/get_next_line.h"
#include "pipex_bonus.h"

void	get_input_here_doc(char **pipe_input, char **limiter)
{
	char	*buffer;

	while (1)
	{
		write(STDOUT_FILENO, "here_doc> ", 10);
		buffer = get_next_line(STDIN_FILENO);
		if (!buffer)
			ft_free_and_exit(limiter, pipe_input);
		if (ft_strcmp(buffer, *limiter))
			break ;
		*pipe_input = ft_strjoin_here_doc(*pipe_input, buffer);
		if (!*pipe_input)
			ft_free_and_exit(&buffer, limiter);
		ft_free_void(&buffer, NULL);
	}
	ft_free_void(&buffer, limiter);
}

void	handle_limiter(t_pipes pipes, char *limiter)
{
	char	*pipe_input;

	limiter = ft_strjoin(limiter, "\n");
	if (!limiter)
		exit(EXIT_FAILURE);
	pipe_input = malloc(1);
	if (!pipe_input)
		ft_free_and_exit(&limiter, NULL);
	pipe_input[0] = '\0';
	get_input_here_doc(&pipe_input, &limiter);
	if (pipe_input || *pipe_input)
	{
		write(pipes.curr_write, pipe_input, ft_strlen(pipe_input));
		ft_free_void(&pipe_input, NULL);
	}
}

void	do_middle_cmd_here_doc(t_pipes pipes, char *argv, char *envp[])
{
	dup2(pipes.prev_read, STDIN_FILENO);
	dup2(pipes.curr_write, STDOUT_FILENO);
	close(pipes.curr_write);
	close(pipes.prev_read);
	find_path(argv, envp);
}

void	do_last_cmd_here_doc(int argc, t_pipes pipes, char *argv[],
		char *envp[])
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

int	here_doc(int argc, char *argv[], char *envp[])
{
	t_pipes	pipes;
	char	*limiter;
	int		pid;
	int		status;
	int		i;

	i = -1;
	status = 0;
	limiter = argv[2];
	pid = 0;
	ft_bzero(&pipes, sizeof(t_pipes));
	init_pipe(&pipes);
	handle_limiter(pipes, limiter);
	while (++i < argc - 5)
		setup_middle_cmd_hd(&pipes, argv[3 + i], envp);
	close(pipes.curr_write);
	if (pid > 0)
		pid = fork();
	pid_check(pid);
	if (pid == 0)
		do_last_cmd_here_doc(argc, pipes, argv, envp);
	wait_for_processes(pid, argc, &status);
	if (pid > 0)
		close_pipes(pipes);
	exit(check_status(status));
}
