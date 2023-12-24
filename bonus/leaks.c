/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   leaks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/14 14:38:02 by rfinneru      #+#    #+#                 */
/*   Updated: 2023/12/15 11:36:33 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_free_void(char **input, char **input2)
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

char	*ft_free_and_exit(char **input, char **input2)
{
	ft_free_void(input, NULL);
	ft_free_void(input2, NULL);
	exit(EXIT_FAILURE);
}

void	ft_free_dbl_arr(int i, char ***input)
{
	i++;
	while ((*input)[i])
	{
		if ((*input)[i])
			free((*input)[i]);
		(i)++;
	}
}

void	ft_free_dbl_arr_exit(int i, char ***input, char **input2)
{
	if (*input2)
		ft_free_void(input2, NULL);
	i++;
	while ((*input)[i])
	{
		if ((*input)[i])
			free((*input)[i]);
		(i)++;
	}
	exit(EXIT_FAILURE);
}
