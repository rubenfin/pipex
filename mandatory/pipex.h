/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/20 11:01:12 by rfinneru      #+#    #+#                 */
/*   Updated: 2023/12/16 13:00:50 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// status
int		check_status(int status);

// path
char	**get_path(char *envp[]);
char	*access_check(char **env_var, char *command);
void	*find_path(char *argv, char *envp[]);

// leaks
void	ft_free_void_man(char **input, char **input2);
char	*ft_free_and_exit_man(char **input, char **input2);
void	ft_free_dbl_arr_man(int i, char ***input);
void	ft_free_dbl_arr_exit_man(int i, char ***input, char **input2);

// pipex utils
int		ft_strlen(char *str);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char c);
void	*ft_memmove(void *dest, const void *src, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);