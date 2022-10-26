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

char	*substitute_line(char *line, char **envp)
{
	char	*ptr;
	int		pre_sub_len;
	char	*new_line;

	ptr = line;
	while (ptr && *ptr != '\0')
	{
		while (*ptr != '$' && *ptr != '\0')
			ptr++;
		if (!*ptr || !*(ptr + 1))
			break ;
		if (!ft_isalpha(*(ptr + 1)))
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
