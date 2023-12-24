/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   security.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 12:14:01 by rfinneru      #+#    #+#                 */
/*   Updated: 2023/12/17 12:55:21 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
		{
			return (0);
		}
		i++;
	}
	if ((s2[i] && !s1[i]) || (s1[i] && !s2[i]))
		return (0);
	return (1);
}

int	argc_heredoc_check(int argc, char *argv[], char *envp[])
{
	if (ft_strcmp(argv[1], "here_doc"))
	{
		if (argc < 6)
		{
			perror("usage: ./pipex here_doc LIMITER \"cmd1\" \"cmd2\" outfile");
			exit(EXIT_FAILURE);
		}
		here_doc(argc, argv, envp);
	}
	if (argc < 5)
	{
		perror("usage: ./pipex infile \"cmd1\" \"cmd2\" outfile");
		exit(EXIT_FAILURE);
	}
	return (0);
}

int	check_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (127);
}

void	wait_for_processes(int pid, int argc, int *status)
{
	int	i;

	i = 0;
	if (pid > 0)
	{
		while (i > argc - 4)
		{
			wait(NULL);
			i++;
		}
		waitpid(pid, &(*status), 0);
	}
}

void	pid_check(int pid)
{
	if (pid == -1)
		exit(EXIT_FAILURE);
}
