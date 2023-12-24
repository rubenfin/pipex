/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/20 10:57:39 by rfinneru      #+#    #+#                 */
/*   Updated: 2023/12/14 15:58:38 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*full_s;
	int		i;
	int		j;

	full_s = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!full_s)
	{
		return (NULL);
	}
	i = 0;
	j = 0;
	while (s1[j])
		full_s[i++] = s1[j++];
	while (*s2)
		full_s[i++] = *(s2++);
	full_s[i] = '\0';
	return (full_s);
}

char	*ft_strjoin_here_doc(char *s1, char *s2)
{
	char	*full_s;
	int		i;
	int		j;

	full_s = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!full_s)
	{
		return (NULL);
	}
	i = 0;
	j = 0;
	while (s1[j])
		full_s[i++] = s1[j++];
	while (*s2)
		full_s[i++] = *(s2++);
	full_s[i] = '\0';
	free(s1);
	return (full_s);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	int		x;

	i = 0;
	if (little[i] == '\0')
		return ((char *)big);
	while (*big && i < len)
	{
		x = 0;
		while (*big == *little && i < len)
		{
			x++;
			little++;
			big++;
			if (*little == '\0')
				return ((char *)big - x);
			i++;
		}
		i -= x;
		little -= x;
		big -= x;
		big++;
		i++;
	}
	return (0);
}

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*p;

	i = 0;
	p = (unsigned char *)s;
	while (i < n)
	{
		p[i] = '\0';
		i++;
	}
}
