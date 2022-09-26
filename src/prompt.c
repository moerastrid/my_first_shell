/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/26 18:05:32 by ageels        #+#    #+#                 */
/*   Updated: 2022/09/26 20:32:51 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	my_signals(void)
{
	int			my_signal;
	sigset_t	my_first_set;

	my_signal = 0;
	sigemptyset(&my_first_set);
	sigaddset(&my_first_set, my_signal);
}

int	prompt(void)
{
	char		*line;

	line = NULL;
	my_signals();
	while (1)
	{
		if (line)
			free (line);
		line = readline(" my_first_shell > ");
		if (!line)
			return (1);
		if (line && *line)
			add_history (line);
	}
	free (line);
	rl_clear_history();
	return (0);
}
