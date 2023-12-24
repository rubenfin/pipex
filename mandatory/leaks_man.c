/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   leaks_man.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/16 11:51:27 by rfinneru      #+#    #+#                 */
/*   Updated: 2023/12/16 14:39:22 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_void_man(char **input, char **input2)
{
	if (input && *input)
	{
		free(*input);
		*input = NULL;
	}
	if (input2 && *input2)
	{
		free(*input2);
		*input2 = NULL;
	}
}

char	*ft_free_and_exit_man(char **input, char **input2)
{
	ft_free_void_man(input, NULL);
	ft_free_void_man(input2, NULL);
	exit(EXIT_FAILURE);
}

void	ft_free_dbl_arr_man(int i, char ***input)
{
	i++;
	while ((*input)[i])
	{
		if ((*input)[i])
			free((*input)[i]);
		i++;
	}
}

void	ft_free_dbl_arr_exit_man(int i, char ***input, char **input2)
{
	if (*input2)
		ft_free_void_man(input2, NULL);
	i++;
	while ((*input)[i])
	{
		if ((*input)[i])
			free((*input)[i]);
		i++;
	}
	exit(EXIT_FAILURE);
}

int	check_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (127);
}
