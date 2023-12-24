/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 12:10:56 by rfinneru      #+#    #+#                 */
/*   Updated: 2023/12/16 13:15:40 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**get_path(char *envp[])
{
	char	**paths;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == NULL)
	{
		i++;
	}
	if (ft_strnstr(envp[i], "PATH", 4) == NULL)
		return (0);
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
	{
		perror("malloc in get_path()");
		return (0);
	}
	return (paths);
}

char	*access_check(char **env_var, char *command)
{
	char	*path;
	char	*path_command;
	int		i;

	i = -1;
	if (access(command, X_OK) == 0)
		return (command);
	while (env_var[++i])
	{
		path = ft_strjoin(env_var[i], "/");
		if (!path)
			ft_free_dbl_arr_exit(i, &env_var, &command);
		free(env_var[i]);
		path_command = ft_strjoin(path, command);
		if (!path_command)
			ft_free_dbl_arr_exit(i, &env_var, &command);
		free(path);
		if (access(path_command, X_OK) == 0)
		{
			ft_free_dbl_arr(i, &env_var);
			return (path_command);
		}
		free(path_command);
	}
	return (NULL);
}

void	*find_path(char *argv, char *envp[])
{
	char	**command;
	char	*path_command;
	char	**env_var;

	command = ft_split(argv, ' ');
	if (!command)
		exit(EXIT_FAILURE);
	env_var = get_path(envp);
	if (!env_var)
		ft_free_and_exit(&command[0], &command[1]);
	path_command = access_check(env_var, command[0]);
	if (!path_command)
	{
		perror("command not found");
		ft_free_and_exit(&command[0], &command[1]);
	}
	execve(path_command, command, envp);
	perror("did not execute path");
	ft_free_void(&path_command, NULL);
	ft_free_and_exit(&command[0], &command[1]);
	exit(EXIT_FAILURE);
}
