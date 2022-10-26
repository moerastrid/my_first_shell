/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 15:09:05 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/26 20:05:41 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

char	*prompt(t_cmd *cmd)
{
	char	*line;

	catch_signals();
	line = readline(PROMPT);
	if (line == NULL)
	{
		clear_cmd(cmd);
		exit(0);
	}
	if (*line)
		add_history(line);
	default_signals();
	return (line);
}

void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
