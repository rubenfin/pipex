/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/20 10:57:39 by rfinneru      #+#    #+#                 */
/*   Updated: 2023/12/16 13:00:08 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*dest_p;
	const char	*src_p;

	if (!dest && !src)
		return (NULL);
	src_p = (const char *)src;
	dest_p = (char *)dest;
	if (dest_p > src_p && dest_p < src_p + n)
	{
		dest_p += n - 1;
		src_p += n - 1;
		while (n--)
		{
			*dest_p-- = *src_p--;
		}
	}
	else
	{
		while (n--)
		{
			*dest_p++ = *src_p++;
		}
	}
	return (dest);
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
