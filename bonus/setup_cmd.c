/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_cmd.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 12:17:14 by rfinneru      #+#    #+#                 */
/*   Updated: 2023/12/20 12:21:01 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	setup_first_cmd(t_pipes *pipes, char *argv[], char **env_var)
{
	int	pid;

	if (init_pipe(pipes) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	pid_check(pid);
	if (pid == 0)
		do_first_cmd(*pipes, argv, env_var);
}

void	setup_middle_cmd(t_pipes *pipes, char *argv, char **env_var)
{
	int	pid;

	if (init_pipe(pipes) == -1)
		exit(1);
	close(pipes->prev_write);
	pid = fork();
	pid_check(pid);
	if (pid == 0)
		do_middle_cmd(*pipes, argv, env_var);
}

void	setup_last_cmd(int argc, t_pipes pipes, char *argv[], char *envp[])
{
	int	pid;

	pid = fork();
	pid_check(pid);
	if (pid == 0)
		do_last_cmd(argc, pipes, argv, envp);
}

void	setup_middle_cmd_hd(t_pipes *pipes, char *argv, char *envp[])
{
	int	pid;

	if (init_pipe(pipes) == -1)
		exit(EXIT_FAILURE);
	close(pipes->prev_write);
	pid = fork();
	pid_check(pid);
	if (pid == 0)
		do_middle_cmd_here_doc(*pipes, argv, envp);
}
