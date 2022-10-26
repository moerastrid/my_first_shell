/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils00.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/27 20:46:11 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/26 17:45:14 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_count(char const *s, char c, int *parts, int *cC)
{
	int		i;

	i = 0;
	while (s[i] != 0 && s[i] == c)
	{
		i++;
		(*cC)++;
	}
	while (s[i] != 0)
	{
		if (s[i] == c)
		{
			while (s[i] != 0 && s[i] == c)
			{
				i++;
				(*cC)++;
			}
			if (s[i] == 0)
				return ;
			(*parts)++;
		}
		else
			i++;
	}
}

static void	ft_enter_data(void	*startptr, int flen, char const *s, char c)
{
	int		i;
	int		j;
	int		skp;

	i = 0;
	j = 0;
	skp = 0;
	if (s[i] != c)
	{
		((char **)startptr)[j] = &((char *)startptr)[flen];
		j++;
	}
	while (s[i] != 0)
	{
		if (s[i] == c && s[i] == s[i + 1] && s[i + 1] != '\0')
			skp++;
		if (s[i] == c && s[i] != s[i + 1] && s[i + 1] != '\0')
		{
			((char **)startptr)[j] = &((char *)startptr)[i + flen + 1 - skp];
			j++;
		}
		else if (s[i] != c)
			((char *)startptr)[i + flen - skp] = s[i];
		i++;
	}
}

char	**single_split(char const *s, char c)
{
	int		flen;
	int		cc;
	void	*startptr;
	int		parts;

	parts = 1;
	cc = 0;
	ft_count(s, c, &parts, &cc);
	flen = sizeof(char *) * (parts + 1);
	startptr = ft_calloc((flen + ft_strlen(s) - cc + parts), 1);
	if (startptr == 0)
		return (NULL);
	if (*s == '\0')
	{
		((char **)startptr)[0] = NULL;
		return ((char **)startptr);
	}
	ft_enter_data(startptr, flen, s, c);
	return ((char **)startptr);
}
