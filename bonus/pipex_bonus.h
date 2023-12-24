/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_bonus.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/20 11:01:12 by rfinneru      #+#    #+#                 */
/*   Updated: 2023/12/15 11:36:44 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipes
{
	int	curr_write;
	int	curr_read;
	int	prev_write;
	int	prev_read;
}		t_pipes;

// here_doc
int		here_doc(int argc, char *argv[], char *envp[]);

// path
char	**get_path(char *envp[]);
void	*find_path(char *argv, char *envp[]);

// pipes
int		init_pipe(t_pipes *pipes);
void	close_pipes(t_pipes pipes);

// security
int		argc_heredoc_check(int argc, char *argv[], char *envp[]);
int		check_status(int status);
void	wait_for_processes(int pid, int argc, int *status);
void	pid_check(int pid);

// leaks
void	ft_free_void(char **input, char **input2);
char	*ft_free_and_exit(char **input, char **input2);
void	ft_free_dbl_arr(int i, char ***input);
void	ft_free_dbl_arr_exit(int i, char ***input, char **input2);

// setup commands
void	setup_first_cmd(t_pipes *pipes, char *argv[], char **envp);
void	setup_middle_cmd(t_pipes *pipes, char *argv, char **envp);
void	setup_last_cmd(int argc, t_pipes pipes, char *argv[], char *envp[]);
void	setup_middle_cmd_hd(t_pipes *pipes, char *argv, char *envp[]);

// do commands
void	do_first_cmd(t_pipes pipes, char *argv[], char **envp);
void	do_middle_cmd(t_pipes pipes, char *argv, char **envp);
void	do_last_cmd(int argc, t_pipes pipes, char *argv[], char **envp);
void	do_middle_cmd_here_doc(t_pipes pipes, char *argv, char *envp[]);

// pipex utils
int		ft_strlen(char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strjoin_here_doc(char *s1, char *s2);
char	**ft_split(char const *s, char c);
char	*ft_strtrim(char const *s1, char const *set);
void	*ft_memmove(void *dest, const void *src, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strdup(const char *s);
void	ft_bzero(void *s, size_t n);
int		ft_strcmp(char *s1, char *s2);
#endif // PIPEX_BONUS_H
