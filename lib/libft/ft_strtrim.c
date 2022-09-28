/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tnuyten <tnuyten@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/07 12:16:27 by tnuyten       #+#    #+#                 */
/*   Updated: 2021/10/13 19:42:51 by tnuyten       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
		{
			return (1);
		}
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*s1_end;
	const char	*s1_start;
	char		*res;

	if (!s1)
		return (NULL);
	if (set == NULL || ft_strncmp(set, "", 1) == 0)
		return (ft_strdup(s1));
	s1_start = s1;
	s1_end = ft_strchr(s1, '\0') - 1;
	while (in_set(*s1, set))
	{
		s1++;
		if (s1 == s1_end)
			return (ft_strdup(""));
	}
	while (in_set(*s1_end, set))
		s1_end--;
	res = ft_substr(s1_start, s1 - s1_start, s1_end - s1 + 1);
	return (res);
}
