/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split_multiple.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: tnuyten <tnuyten@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/07 18:18:52 by tnuyten       #+#    #+#                 */
/*   Updated: 2022/10/24 16:34:15 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char			*get_end_index(char *s, char *c);
static size_t		count_words(char const *s, char *c);
static int			fill_array(char **res, char *s, size_t len, char *c);

char	**ft_split_multiple(char const *s, char *c)
{
	size_t		len;
	char		**res;

	if (!s)
		return (NULL);
	len = count_words(s, c) + 1;
	res = malloc(len * sizeof(char *));
	if (!res)
		return (NULL);
	if (fill_array(res, (char *)s, len, c) == 0)
	{
		while (*res)
			free(*res++);
		free(res);
		return (NULL);
	}
	return (res);
}

static int	in(char s, char *c)
{
	while (c && *c)
	{
		if (*c == s)
			return (1);
		c++;
	}
	return (0);
}

static int	fill_array(char **res, char *s, size_t len, char *c)
{
	size_t		i;
	char		*end_index;

	i = 0;
	while (i + 1 < len)
	{
		while (in(*s, c) && !in('\0', c))
			s++;
		end_index = get_end_index(s, c);
		if (end_index - s < 0)
			return (0);
		res[i] = ft_substr(s, 0, end_index - s);
		if (res[i] == NULL)
			return (0);
		i++;
		s = end_index;
	}
	res[i] = NULL;
	return (1);
}

static size_t	count_words(char const *s, char *c)
{
	size_t		word_count;
	char const	*s2;

	s2 = s;
	word_count = 0;
	while (*s2)
	{
		while (in(*s2, c))
			s2++;
		if (!in(*s2, c) && *s2 != '\0')
		{
			word_count++;
			while (!in(*s2, c) && *s2 != '\0')
			{
				s2++;
			}
		}
	}
	return (word_count);
}

static char	*get_end_index(char *s, char *c)
{
	while (s && *s)
	{
		if (in(*s, c))
			return (s);
		s++;
	}
	return (s);
}
