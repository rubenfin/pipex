/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/20 17:44:44 by rfinneru      #+#    #+#                 */
/*   Updated: 2023/12/12 15:06:12 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	free_array(char **split_array, int i)
{
	int	x;

	x = 0;
	while (x < i)
	{
		free(split_array[x]);
		x++;
	}
	free(split_array);
}

static int	count_delimiter(char const *s, char c)
{
	int	count;
	int	inside_word;

	count = 0;
	inside_word = 0;
	while (*s)
	{
		if (*s == c)
		{
			if (inside_word)
			{
				count++;
				inside_word = 0;
			}
		}
		else
		{
			if (!inside_word)
				inside_word = 1;
		}
		s++;
	}
	if (inside_word)
		count++;
	return (count);
}

static int	copy_word(char **split_arr, const char *start, int len, int i)
{
	int	j;

	j = 0;
	split_arr[i] = (char *)malloc(len + 1);
	if (!split_arr[i])
	{
		free_array(split_arr, i);
		return (0);
	}
	while (j < len)
	{
		split_arr[i][j] = start[j];
		j++;
	}
	split_arr[i][j] = '\0';
	return (1);
}

static int	put_words(char **split_arr, const char *s, char c)
{
	int			len;
	const char	*start;
	int			i;
	int			check;

	i = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			start = s;
			while (*s && *s != c)
				s++;
			len = s - start;
			check = copy_word(split_arr, start, len, i);
			if (!check)
				return (0);
			i++;
		}
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	int		del_count;
	int		check;
	char	**split_arr;

	del_count = count_delimiter(s, c);
	split_arr = (char **)malloc((del_count + 1) * sizeof(char *));
	if (!split_arr)
		return (NULL);
	check = put_words(split_arr, s, c);
	if (!check)
		return (NULL);
	split_arr[del_count] = NULL;
	return (split_arr);
}
