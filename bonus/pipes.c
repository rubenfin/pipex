/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 12:12:47 by rfinneru      #+#    #+#                 */
/*   Updated: 2023/12/14 15:52:49 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	init_pipe(t_pipes *pipes)
{
	int	fds[2];

	if (pipes->curr_write)
	{
		pipes->prev_write = pipes->curr_write;
		pipes->prev_read = pipes->curr_read;
	}
	if (pipe(fds) == -1)
		exit(EXIT_FAILURE);
	pipes->curr_write = fds[1];
	pipes->curr_read = fds[0];
	return (0);
}

void	close_pipes(t_pipes pipes)
{
	if (pipes.prev_read)
	{
		close(pipes.prev_write);
		close(pipes.prev_read);
	}
	close(pipes.curr_write);
	close(pipes.curr_read);
}
