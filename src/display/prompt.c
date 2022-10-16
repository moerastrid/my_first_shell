/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 15:09:05 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/14 12:54:57 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

char	*prompt(t_cmd *cmd)
{
	char	*line;

	line = readline(PROMPT);
	if (line == NULL)
	{
		clear_cmd(cmd);
		exit(0);
	}
	if (*line)
		add_history(line);
	return (line);
}
