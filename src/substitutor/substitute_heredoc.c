/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   substitute_heredoc.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 16:59:57 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/26 19:22:45 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "substitutor.h"

static int	is_word_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

char	*substitute_line(char *line, char **envp)
{
	char	*ptr;
	int		pre_sub_len;
	char	*new_line;

	ptr = line;
	pre_sub_len = 0;
	while (line && *ptr != '\0')
	{
		while (*ptr != '$' && *ptr != '\0')
			ptr++;
		if (!*ptr || !*(ptr + 1))
			break ;
		if (!is_word_char(*(ptr + 1)))
		{
			ptr++;
			continue ;
		}
		new_line = rep_once(ptr, line, &pre_sub_len, envp);
		free(line);
		line = new_line;
		ptr = line + pre_sub_len;
	}
	return (line);
}
